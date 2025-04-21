# Collision

example:
```csharp
using ErenAydin.DamageNumbers;
using Unity.Burst;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Physics;
using Unity.Physics.Systems;
using Unity.Transforms;
using Zoo.Andrey.Boss;
using Zoo.Andrey.PlayerSetup;
using Zoo.Tan.Script;
using Zoo.Tan.Script.Tags;
using Zoo.Yifei.Scripts.Enums;
using Zoo.Yifei.Scripts.Monster;
using Zoo.Yifei.Scripts.Skill;
using Constants = Zoo.Yifei.Scripts.Skill.Constants;

namespace Zoo.Yifei.Scripts.Systems.Collision
{
    [UpdateInGroup(typeof(FixedStepSimulationSystemGroup))]
    [UpdateAfter(typeof(PhysicsSystemGroup))]
    public partial struct CollisionSystem : ISystem, ISystemStartStop
    {
        private DynamicBuffer<DamageNumberBuffer> _damageTextBuffer;
        private float4 _playerDamageColor;
        private Entity _autoExplosionLogEntity;
        private DynamicBuffer<HitList> _hitList; // auto explosion log / hit buffer from kill entity

        [BurstCompile]
        public void OnCreate(ref SystemState state)
        {
            state.RequireForUpdate<SimulationSingleton>();
            state.RequireForUpdate<DamageTextInitializerComponent>();
            state.RequireForUpdate<PlayerTag>();
            state.RequireForUpdate<AutoExplosionLogTag>();
            _playerDamageColor = new float4(255f / 255f, 182f / 255f, 30f / 255f, 1f);
        }

        [BurstCompile]
        public void OnStartRunning(ref SystemState state)
        {
            _autoExplosionLogEntity = SystemAPI.GetSingletonEntity<AutoExplosionLogTag>();
        }

        [BurstCompile]
        public void OnStopRunning(ref SystemState state)
        {
        }

        [BurstCompile]
        public void OnUpdate(ref SystemState state)
        {
            state.Dependency.Complete();

            var triggerEvents = SystemAPI.GetSingleton<SimulationSingleton>().AsSimulation().TriggerEvents;

            var ecbBeginMonsterSkill = GetBeginEntityCommandBuffer(ref state);
            var ecbEndMonsterSkill = GetEndEntityCommandBuffer(ref state);

            _damageTextBuffer = SystemAPI.GetSingletonBuffer<DamageNumberBuffer>();

            foreach (var triggerEvent in triggerEvents)
            {
                var entityA = triggerEvent.EntityA;
                var entityB = triggerEvent.EntityB;

                var skillEntity = Entity.Null;
                var monsterEntity = Entity.Null;
                var playerEntity = Entity.Null;
                var monsterSkillEntity = Entity.Null;
                var puddleEntity = Entity.Null;

                if (state.EntityManager.HasComponent<SkillVFXTag>(entityA))
                {
                    skillEntity = entityA;
                    if (state.EntityManager.HasComponent<MonsterTag>(entityB))
                        monsterEntity = entityB;
                    else if (state.EntityManager.HasComponent<PlayerTag>(entityB))
                        playerEntity = entityB;
                    else if (state.EntityManager.HasComponent<BossPuddleData>(entityB)) puddleEntity = entityB;
                }
                else if (state.EntityManager.HasComponent<SkillVFXTag>(entityB))
                {
                    skillEntity = entityB;
                    if (state.EntityManager.HasComponent<MonsterTag>(entityA))
                        monsterEntity = entityA;
                    else if (state.EntityManager.HasComponent<PlayerTag>(entityA))
                        playerEntity = entityA;
                    else if (state.EntityManager.HasComponent<BossPuddleData>(entityA)) puddleEntity = entityA;
                }
                else if (state.EntityManager.HasComponent<MonsterSkillTag>(entityA))
                {
                    monsterSkillEntity = entityA;
                    if (state.EntityManager.HasComponent<PlayerTag>(entityB))
                        playerEntity = entityB;
                    else if (state.EntityManager.HasComponent<BossPuddleTag>(entityB)) puddleEntity = entityB;
                }
                else if (state.EntityManager.HasComponent<MonsterSkillTag>(entityB))
                {
                    monsterSkillEntity = entityB;
                    if (state.EntityManager.HasComponent<PlayerTag>(entityA))
                        playerEntity = entityA;
                    else if (state.EntityManager.HasComponent<BossPuddleTag>(entityA)) puddleEntity = entityA;
                }

                if (skillEntity != Entity.Null)
                {
                    var skillElementVfxDamageData =
                        state.EntityManager.GetComponentData<SkillElementVFXDamageData>(skillEntity);
                    if (skillElementVfxDamageData.HasDelayTime < skillElementVfxDamageData.DelayTime)
                    {
                        skillElementVfxDamageData.HasDelayTime += SystemAPI.Time.DeltaTime;
                        state.EntityManager.SetComponentData(skillEntity, skillElementVfxDamageData);
                        continue;
                    }

                    if (state.EntityManager.HasBuffer<HitList>(skillEntity))
                        _hitList = state.EntityManager.GetBuffer<HitList>(skillEntity);
                    else if (state.EntityManager.HasComponent<AutoExplosionTag>(skillEntity))
                        _hitList = state.EntityManager.GetBuffer<HitList>(_autoExplosionLogEntity);

                    // if is periodic damage, remove the old hit over the time
                    if (skillElementVfxDamageData.DamageType == DamageTypeEnum.PeriodicValueDamage)
                        for (var i = _hitList.Length - 1; i >= 0; i--)
                            if (SystemAPI.Time.ElapsedTime - _hitList[i].Time > skillElementVfxDamageData.PeriodicTime)
                                _hitList.RemoveAt(i);

                    if (monsterEntity != Entity.Null)
                    {
                        HandleMonsterAndSkill(ref state, monsterEntity, skillEntity, ref _hitList,
                            skillElementVfxDamageData);
                    }
                    else if (playerEntity != Entity.Null)
                    {
                        var isPlayerHit = false;
                        for (var i = 0; i < _hitList.Length; i++)
                            if (SystemAPI.Exists(_hitList[i].Entity) && _hitList[i].Entity == playerEntity)
                            {
                                isPlayerHit = true;
                                break;
                            }

                        if (isPlayerHit) continue;

                        var playerData = state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                        var damageValue = skillElementVfxDamageData.DamageValue;
                        if (skillElementVfxDamageData.DamageType == DamageTypeEnum.DirectPercentageDamage)
                            damageValue *= playerData.ValueRO.MaxHealth;
                        playerData.ValueRW.PendingDamage += damageValue;

                        _hitList.Add(new HitList { Entity = playerEntity, Time = SystemAPI.Time.ElapsedTime });

                        var localTransform = state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                        _damageTextBuffer.Add(new DamageNumberBuffer
                        {
                            position = localTransform.Position,
                            color = _playerDamageColor,
                            damageNumber = (uint)damageValue,
                            scale = math.max(1.2f, math.min(2f, damageValue / Constants.DamageTextBaseScaleFactor))
                        });
                    }
                }
                else if (monsterSkillEntity != Entity.Null)
                {
                    if (playerEntity != Entity.Null)
                    {
                        if (state.EntityManager.HasComponent<WindBallData>(monsterSkillEntity))
                        {
                            var playerData =
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            var windBallData = state.EntityManager.GetComponentDataRW<WindBallData>(monsterSkillEntity);
                            playerData.ValueRW.PendingDamage += windBallData.ValueRO.Damage;
                            windBallData.ValueRW.HasHitPlayer = true;

                            var localTransform = state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                            _damageTextBuffer.Add(new DamageNumberBuffer
                            {
                                position = localTransform.Position,
                                color = _playerDamageColor,
                                damageNumber = (uint)windBallData.ValueRO.Damage,
                                scale = math.max(1.2f,
                                    math.min(2f, windBallData.ValueRO.Damage / Constants.DamageTextBaseScaleFactor))
                            });
                        }
                        else if (state.EntityManager.HasComponent<BossPuddleElectricityData>(monsterSkillEntity))
                        {
                            var playerData =
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            var bossPuddleElectricityData =
                                state.EntityManager.GetComponentDataRW<BossPuddleElectricityData>(monsterSkillEntity);
                            if (SystemAPI.Time.ElapsedTime - bossPuddleElectricityData.ValueRO.LastHitTime >
                                bossPuddleElectricityData.ValueRO.HitInterval)
                            {
                                bossPuddleElectricityData.ValueRW.LastHitTime = SystemAPI.Time.ElapsedTime;
                                playerData.ValueRW.PendingDamage += bossPuddleElectricityData.ValueRO.Damage;
                            }

                            var localTransform = state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                            _damageTextBuffer.Add(new DamageNumberBuffer
                            {
                                position = localTransform.Position,
                                color = _playerDamageColor,
                                damageNumber = (uint)bossPuddleElectricityData.ValueRO.Damage,
                                scale = math.max(1.2f,
                                    math.min(2f,
                                        bossPuddleElectricityData.ValueRO.Damage / Constants.DamageTextBaseScaleFactor))
                            });
                        }
                        else if (state.EntityManager.HasComponent<BossBallData>(monsterSkillEntity))
                        {
                            var playerData =
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            var bossBallData = state.EntityManager.GetComponentDataRW<BossBallData>(monsterSkillEntity);
                            playerData.ValueRW.PendingDamage += bossBallData.ValueRO.Damage;
                            bossBallData.ValueRW.HasHitPlayer = true;

                            var localTransform = state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                            _damageTextBuffer.Add(new DamageNumberBuffer
                            {
                                position = localTransform.Position,
                                color = _playerDamageColor,
                                damageNumber = (uint)bossBallData.ValueRO.Damage,
                                scale = math.max(1.2f,
                                    math.min(2f, bossBallData.ValueRO.Damage / Constants.DamageTextBaseScaleFactor))
                            });
                        }
                        else if (state.EntityManager.HasComponent<TrapData>(monsterSkillEntity))
                        {
                            var trapData = state.EntityManager.GetComponentDataRW<TrapData>(monsterSkillEntity);

                            var playerData =
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            if (trapData.ValueRO.TrapTime <= 0)
                            {
                                ecbEndMonsterSkill.DestroyEntity(0, monsterSkillEntity);
                                playerData.ValueRW.CurrentSpeed = playerData.ValueRO.Speed;
                            }
                            else
                            {
                                trapData.ValueRW.TrapTime -= SystemAPI.Time.DeltaTime;
                                playerData.ValueRW.CurrentSpeed = 0;
                            }
                        }
                        else if (state.EntityManager.HasComponent<ExplosionData>(monsterSkillEntity))
                        {
                            var explosionData = state.EntityManager.GetComponentData<ExplosionData>(monsterSkillEntity);
                            var playerData = 
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            playerData.ValueRW.PendingDamage += explosionData.Damage;
                            ecbEndMonsterSkill.DestroyEntity(0, monsterSkillEntity);

                            var localTransform =
                                state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                            _damageTextBuffer.Add(new DamageNumberBuffer
                            {
                                position = localTransform.Position,
                                color = _playerDamageColor,
                                damageNumber = (uint)explosionData.Damage,
                                scale = math.max(1.2f,
                                    math.min(2f, explosionData.Damage / Constants.DamageTextBaseScaleFactor))
                            });
                        }
                        else if (state.EntityManager.HasComponent<NormalAttackData>(monsterSkillEntity))
                        {
                            var normalAttackData =
                                state.EntityManager.GetComponentData<NormalAttackData>(monsterSkillEntity);
                            var playerData =
                                state.EntityManager.GetComponentDataRW<PlayerEntityParameters>(playerEntity);
                            playerData.ValueRW.PendingDamage += normalAttackData.Damage;
                            ecbEndMonsterSkill.DestroyEntity(0, monsterSkillEntity);

                            var localTransform = state.EntityManager.GetComponentData<LocalTransform>(playerEntity);
                            _damageTextBuffer.Add(new DamageNumberBuffer
                            {
                                position = localTransform.Position,
                                color = _playerDamageColor,
                                damageNumber = (uint)normalAttackData.Damage,
                                scale = math.min(normalAttackData.Damage / Constants.DamageTextBaseScaleFactor, 2f)
                            });
                        }
                    }
                }

                if (puddleEntity != Entity.Null)
                {
                    if (monsterSkillEntity != Entity.Null)
                    {
                        // handle puddle and electricity puddle
                        if (state.EntityManager.HasComponent<BossBallData>(monsterSkillEntity))
                        {
                            var bossPuddleData = state.EntityManager.GetComponentDataRW<BossPuddleData>(puddleEntity);
                            if (bossPuddleData.ValueRO.ElectricityPuddleEntity != Entity.Null)
                            {
                                if (bossPuddleData.ValueRO.TriggerTime < bossPuddleData.ValueRO.TriggeredLifeTime)
                                    bossPuddleData.ValueRW.TriggerTime = 0;
                            }
                            else
                            {
                                var bossData = SystemAPI.GetSingleton<BossData>();
                                var electricityPuddleEntity =
                                    state.EntityManager.Instantiate(bossData.WaterElectricity);
                                state.EntityManager.SetComponentData(electricityPuddleEntity, new LocalTransform
                                {
                                    Position = state.EntityManager.GetComponentData<LocalTransform>(puddleEntity)
                                        .Position,
                                    Rotation = quaternion.identity,
                                    Scale = 1
                                });
                                bossPuddleData.ValueRW.ElectricityPuddleEntity = electricityPuddleEntity;
                                bossPuddleData.ValueRW.TriggerTime = 0;
                            }
                        }
                    }
                    else if (skillEntity != null)
                    {
                        var skillData = state.EntityManager.GetComponentData<SkillElementVFXDamageData>(skillEntity);
                        var bossPuddleData = state.EntityManager.GetComponentDataRW<BossPuddleData>(puddleEntity);
                        if (skillData.Element == ElementEnum.Fire) bossPuddleData.ValueRW.HitByFire = true;
                    }
                }
            }
        }

        [BurstCompile]
        public void OnDestroy(ref SystemState state)
        {
        }

        private EntityCommandBuffer.ParallelWriter GetBeginEntityCommandBuffer(ref SystemState state)
        {
            var ecbSingleton = SystemAPI.GetSingleton<BeginSimulationEntityCommandBufferSystem.Singleton>();
            var ecb = ecbSingleton.CreateCommandBuffer(state.WorldUnmanaged);
            return ecb.AsParallelWriter();
        }

        private EntityCommandBuffer.ParallelWriter GetEndEntityCommandBuffer(ref SystemState state)
        {
            var ecbSingleton = SystemAPI.GetSingleton<EndSimulationEntityCommandBufferSystem.Singleton>();
            var ecb = ecbSingleton.CreateCommandBuffer(state.WorldUnmanaged);
            return ecb.AsParallelWriter();
        }

        private void HandleMonsterAndSkill(ref SystemState state, Entity monsterEntity, Entity skillEntity,
            ref DynamicBuffer<HitList> hitList, SkillElementVFXDamageData skillElementVfxDamageData)
        {
            var damageColor = new float4(0.8f, 0.8f, 0.8f, 1f);

            HandleSpecificSkill(ref state, monsterEntity, skillEntity);

            float damageValue = 0;
            for (var i = 0; i < hitList.Length; i++)
                if (SystemAPI.Exists(hitList[i].Entity) && hitList[i].Entity == monsterEntity)
                    return;

            if (state.EntityManager.HasComponent<BossTag>(monsterEntity))
            {
                // handle boss
                var bossData = state.EntityManager.GetComponentDataRW<BossData>(monsterEntity);
                var monsterResistanceData = state.EntityManager.GetComponentData<MonsterResistanceData>(monsterEntity);
                damageValue = skillElementVfxDamageData.DamageValue;
                if (skillElementVfxDamageData.DamageType == DamageTypeEnum.DirectPercentageDamage)
                    damageValue *= bossData.ValueRO.MaxHp;

                if (skillElementVfxDamageData.Element == ElementEnum.Fire)
                {
                    damageValue *= 1 - monsterResistanceData.FireResistance;
                    damageColor = DamageColorEnum.Fire;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Water)
                {
                    damageValue *= 1 - monsterResistanceData.WaterResistance;
                    damageColor = DamageColorEnum.Water;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Lightning)
                {
                    damageValue *= 1 - monsterResistanceData.LightningResistance;
                    damageColor = DamageColorEnum.Lightning;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Wind)
                {
                    damageValue *= 1 - monsterResistanceData.WindResistance;
                    damageColor = DamageColorEnum.Wind;
                }

                bossData.ValueRW.PendingDamage += damageValue;
            }
            else
            {
                // handle mosnter
                var monsterData = state.EntityManager.GetComponentDataRW<MonsterData>(monsterEntity);
                var monsterResistanceData = state.EntityManager.GetComponentData<MonsterResistanceData>(monsterEntity);
                damageValue = skillElementVfxDamageData.DamageValue;
                if (skillElementVfxDamageData.DamageType == DamageTypeEnum.DirectPercentageDamage)
                    damageValue *= monsterData.ValueRO.MaxHp;

                if (skillElementVfxDamageData.Element == ElementEnum.Fire)
                {
                    damageValue *= 1 - monsterResistanceData.FireResistance;
                    damageColor = DamageColorEnum.Fire;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Water)
                {
                    damageValue *= 1 - monsterResistanceData.WaterResistance;
                    damageColor = DamageColorEnum.Water;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Lightning)
                {
                    damageValue *= 1 - monsterResistanceData.LightningResistance;
                    damageColor = DamageColorEnum.Lightning;
                }
                else if (skillElementVfxDamageData.Element == ElementEnum.Wind)
                {
                    damageValue *= 1 - monsterResistanceData.WindResistance;
                    damageColor = DamageColorEnum.Wind;
                }

                monsterData.ValueRW.PendingDamage += damageValue;
            }

            hitList.Add(new HitList { Entity = monsterEntity, Time = SystemAPI.Time.ElapsedTime });

            var localTransform = state.EntityManager.GetComponentData<LocalTransform>(monsterEntity);

            _damageTextBuffer.Add(new DamageNumberBuffer
            {
                position = localTransform.Position,
                color = damageColor,
                damageNumber = (uint)damageValue,
                scale = math.max(damageValue / Constants.DamageTextBaseScaleFactor, 0.8f)
            });
        }

        private void HandleSpecificSkill(ref SystemState state, Entity hitEntity, Entity skillEntity)
        {
            if (state.EntityManager.HasComponent<WhirlTag>(skillEntity))
            {
                var whirlTag = state.EntityManager.GetComponentData<WhirlTag>(skillEntity);
                // 计算skill的位置，然后将hitEntity逆时针吸引向skill的方向
                var skillTransform = state.EntityManager.GetComponentData<LocalTransform>(skillEntity);
                var hitTransform = state.EntityManager.GetComponentData<LocalTransform>(hitEntity);
                var skillPosition = new float3(skillTransform.Position.x, 0, skillTransform.Position.z);
                var hitPosition = new float3(hitTransform.Position.x, 0, hitTransform.Position.z);
                var direction = hitPosition - skillPosition;
                var normalizedDirection = math.normalizesafe(direction, float3.zero);
                var perpendicularDirection = new float3(-normalizedDirection.z, 0, normalizedDirection.x);
                // 逆时针吸引 + 向中心吸引
                var newPosition = hitPosition -
                                  (perpendicularDirection * whirlTag.WhirlSpeed + direction * whirlTag.WhirlSpeed) *
                                  SystemAPI.Time.DeltaTime;
                hitTransform.Position = newPosition;
                // 根据Constants的数据，当怪物位置在地图之外时，设置为最近的地图边界
                hitTransform.Position.x = math.clamp(hitTransform.Position.x, Constants.MapLeft + 5, Constants.MapRight - 5);
                hitTransform.Position.z = math.clamp(hitTransform.Position.z, Constants.MapBottom + 5, Constants.MapTop - 5);
                state.EntityManager.SetComponentData(hitEntity, hitTransform);
            }
        }
    }
}
```