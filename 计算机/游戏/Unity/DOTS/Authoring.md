# Authoring

Example:
```csharp
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;
using Zoo.Yifei.Scripts.Enums;
using Random = UnityEngine.Random;

namespace Zoo.Yifei.Scripts.Skill
{
    public struct SkillSpawnerPrefabs : IComponentData
    {
        // skill
        public Entity BlazingTrailPeriodicSkillContainerEntity;
        public Entity BlazingTrailVFXEntityPrefab;
        public Entity SmallTornadoMovableSkillContainerEntity;
        public Entity SmallTornadoVFXEntityPrefab;
        public Entity WhirlPoolPeriodicSkillContainerEntity;

        public Entity WhirlPoolVFXEntityPrefab;

        // public Entity ChainLightningPeriodicSkillContainerEntity;
        public Entity ChainLightningVFXEntityPrefab;
        public Entity ChainLightningCollisionEntityPrefab;

        // trigger explosion skill
        public Entity ElementConflictExplosionPeriodicSkillContainerEntity;
        public Entity ElementConflictExplosionVFXEntityPrefab;
        public Entity BlazingLavaPeriodicSkillContainerEntity;
        public Entity BlazingLavaVFXEntityPrefab;
        public Entity FireTornadoMovableSkillContainerEntity;
        public Entity FireTornadoVFXEntityPrefab;
        public Entity WindTornadoMovableSkillContainerEntity;
        public Entity WindTornadoVFXEntityPrefab;
        public Entity WaterTornadoMovableSkillContainerEntity;
        public Entity WaterTornadoVFXEntityPrefab;
        public Entity BigPoolPeriodicSkillContainerEntity;
        public Entity BigPoolVFXEntityPrefab;
        public Entity LightningStrikeWaterPeriodicSkillContainerEntity;
        public Entity LightningStrikeWaterVFXEntityPrefab;
        public Entity FireFromLightningPeriodicSkillContainerEntity;
        public Entity FireFromLightningVFXEntityPrefab;

        // Big VFX - when triggered ppm of one element >= threshold
        public Entity SmallTsunamiMovableSkillContainerEntity;
        public Entity SmallTsunamiVFXEntityPrefab;
        public Entity GaleBladeStormMovableSkillContainerEntity;
        public Entity GaleBladeStormVFXEntityPrefab;
        public Entity BigMeteorStrikePeriodicSkillContainerEntity;
        public Entity BigMeteorStrikeVFXEntityPrefab;
        // public Entity ChainLightningRampagePeriodicSkillContainerEntity; // chain lightning is complex scriptable skill

        // auto explosion skill
        public Entity TsunamiMovableSkillContainerEntity;
        public Entity TsunamiVFXEntityPrefab;
        public Entity SuperTornadoMovableSkillContainerEntity;
        public Entity SuperTornadoVFXEntityPrefab;
        public Entity MeteorStrikePeriodicSkillContainerEntity;
        public Entity MeteorStrikeVFXEntityPrefab;
        public Entity LightningStormPeriodicSkillContainerEntity;
        public Entity LightningStormVFXEntityPrefab;
        public Entity LightningStormNoDamagePeriodicSkillContainerEntity;
        public Entity LightningStormNoDamageVFXEntityPrefab;
    }

    internal class SkillAuthoring : MonoBehaviour
    {
        // skill
        public GameObject blazingTrailContainerGameObjectPrefab;
        public GameObject blazingTrailGameObjectPrefab;
        public GameObject smallTornadoContainerGameObjectPrefab;
        public GameObject smallTornadoGameObjectPrefab;
        public GameObject whirlPoolContainerGameObjectPrefab;

        public GameObject whirlPoolGameObjectPrefab;

        // public GameObject chainLightningContainerGameObjectPrefab; // no need, this is special scriptable skill <ChainLightningSystem.cs>
        public GameObject chainLightningGameObjectPrefab;
        public GameObject chainLightningCollisionGameObjectPrefab;

        // trigger explosion skill
        public GameObject elementConflictExplosionContainerGameObjectPrefab;
        public GameObject elementConflictExplosionGameObjectPrefab;
        public GameObject blazingLavaContainerGameObjectPrefab;
        public GameObject blazingLavaGameObjectPrefab;
        public GameObject fireTornadoContainerGameObjectPrefab;
        public GameObject fireTornadoGameObjectPrefab;
        public GameObject windTornadoContainerGameObjectPrefab;
        public GameObject windTornadoGameObjectPrefab;
        public GameObject waterTornadoContainerGameObjectPrefab;
        public GameObject waterTornadoGameObjectPrefab;
        public GameObject bigPoolContainerGameObjectPrefab;

        public GameObject bigPoolGameObjectPrefab;

        // BigChainLightning is use same from skill, it's complex scriptable skill
        public GameObject lightningStrikeWaterContainerGameObjectPrefab;
        public GameObject lightningStrikeWaterGameObjectPrefab;
        public GameObject fireFromLightningContainerGameObjectPrefab;
        public GameObject fireFromLightningGameObjectPrefab;

        // Big VFX - when triggered ppm of one element >= threshold
        public GameObject smallTsunamiContainerGameObjectPrefab;
        public GameObject smallTsunamiGameObjectPrefab;
        public GameObject galeBladeStormContainerGameObjectPrefab;
        public GameObject galeBladeStormGameObjectPrefab;
        public GameObject bigMeteorStrikeContainerGameObjectPrefab;

        public GameObject bigMeteorStrikeGameObjectPrefab;
        // public GameObject ChainLightningRampageContainerGameObjectPrefab; // chain lightning is complex scriptable skill

        // auto explosion skill
        public GameObject tsunamiContainerGameObjectPrefab;
        public GameObject tsunamiGameObjectPrefab;
        public GameObject superTornadoContainerGameObjectPrefab;
        public GameObject superTornadoGameObjectPrefab;
        public GameObject meteorStrikeContainerGameObjectPrefab;
        public GameObject meteorStrikeGameObjectPrefab;
        public GameObject lightningStormContainerGameObjectPrefab;
        public GameObject lightningStormGameObjectPrefab;
        public GameObject lightningStormNoDamageContainerGameObjectPrefab;
        public GameObject lightningStormNoDamageGameObjectPrefab;
    }

    internal class SkillAuthoringBaker : Baker<SkillAuthoring>
    {
        public override void Bake(SkillAuthoring authoring)
        {
            var spawnerEntity = GetEntity(TransformUsageFlags.None);

            // skill
            var blazingTrailVFXEntity = GetEntity(authoring.blazingTrailGameObjectPrefab, TransformUsageFlags.Dynamic);
            var blazingTrailPeriodicSkillContainerEntity = GetEntity(authoring.blazingTrailContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var tornadoVFXEntity = GetEntity(authoring.smallTornadoGameObjectPrefab, TransformUsageFlags.Dynamic);
            var tornadoMovableSkillContainerEntity =
                GetEntity(authoring.smallTornadoContainerGameObjectPrefab, TransformUsageFlags.None);
            var whirlPoolVFXEntity = GetEntity(authoring.whirlPoolGameObjectPrefab, TransformUsageFlags.Dynamic);
            var whirlPoolPeriodicSkillContainerEntity =
                GetEntity(authoring.whirlPoolContainerGameObjectPrefab, TransformUsageFlags.None);
            var chainLightningVFXEntity =
                GetEntity(authoring.chainLightningGameObjectPrefab, TransformUsageFlags.Dynamic);
            var chainLightningCollisionEntity = GetEntity(authoring.chainLightningCollisionGameObjectPrefab,
                TransformUsageFlags.Dynamic);

            // trigger explosion skill
            var elementConflictExplosionVFXEntity = GetEntity(authoring.elementConflictExplosionGameObjectPrefab,
                TransformUsageFlags.Dynamic);
            var elementConflictExplosionPeriodicSkillContainerEntity =
                GetEntity(authoring.elementConflictExplosionContainerGameObjectPrefab, TransformUsageFlags.None);
            var blazingLavaVFXEntity = GetEntity(authoring.blazingLavaGameObjectPrefab, TransformUsageFlags.Dynamic);
            var blazingLavaPeriodicSkillContainerEntity = GetEntity(authoring.blazingLavaContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var fireTornadoVFXEntity = GetEntity(authoring.fireTornadoGameObjectPrefab, TransformUsageFlags.Dynamic);
            var fireTornadoMovableSkillContainerEntity = GetEntity(authoring.fireTornadoContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var windTornadoVFXEntity = GetEntity(authoring.windTornadoGameObjectPrefab, TransformUsageFlags.Dynamic);
            var windTornadoMovableSkillContainerEntity = GetEntity(authoring.windTornadoContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var waterTornadoVFXEntity = GetEntity(authoring.waterTornadoGameObjectPrefab, TransformUsageFlags.Dynamic);
            var waterTornadoMovableSkillContainerEntity = GetEntity(authoring.waterTornadoContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var bigPoolVFXEntity = GetEntity(authoring.bigPoolGameObjectPrefab, TransformUsageFlags.Dynamic);
            var bigPoolPeriodicSkillContainerEntity =
                GetEntity(authoring.bigPoolContainerGameObjectPrefab, TransformUsageFlags.None);
            var lightningStrikeWaterVFXEntity = GetEntity(authoring.lightningStrikeWaterGameObjectPrefab,
                TransformUsageFlags.Dynamic);
            var lightningStrikeWaterPeriodicSkillContainerEntity =
                GetEntity(authoring.lightningStrikeWaterContainerGameObjectPrefab, TransformUsageFlags.None);
            var fireFromLightningVFXEntity =
                GetEntity(authoring.fireFromLightningGameObjectPrefab, TransformUsageFlags.Dynamic);
            var fireFromLightningPeriodicSkillContainerEntity =
                GetEntity(authoring.fireFromLightningContainerGameObjectPrefab, TransformUsageFlags.None);

            // Big VFX - when triggered ppm of one element >= threshold
            var smallTsunamiVFXEntity = GetEntity(authoring.smallTsunamiGameObjectPrefab, TransformUsageFlags.Dynamic);
            var smallTsunamiMovableSkillContainerEntity = GetEntity(authoring.smallTsunamiContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var galeBladeStormVFXEntity =
                GetEntity(authoring.galeBladeStormGameObjectPrefab, TransformUsageFlags.Dynamic);
            var galeBladeStormMovableSkillContainerEntity = GetEntity(authoring.galeBladeStormContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var bigMeteorStrikeVFXEntity =
                GetEntity(authoring.bigMeteorStrikeGameObjectPrefab, TransformUsageFlags.Dynamic);
            var bigMeteorStrikePeriodicSkillContainerEntity =
                GetEntity(authoring.bigMeteorStrikeContainerGameObjectPrefab, TransformUsageFlags.None);

            // auto explosion skill
            var tsunamiVFXEntity = GetEntity(authoring.tsunamiGameObjectPrefab, TransformUsageFlags.Dynamic);
            var tsunamiPeriodicSkillContainerEntity =
                GetEntity(authoring.tsunamiContainerGameObjectPrefab, TransformUsageFlags.None);
            var superTornadoVFXEntity = GetEntity(authoring.superTornadoGameObjectPrefab, TransformUsageFlags.Dynamic);
            var superTornadoMovableSkillContainerEntity = GetEntity(authoring.superTornadoContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var meteorStrikeVFXEntity = GetEntity(authoring.meteorStrikeGameObjectPrefab, TransformUsageFlags.Dynamic);
            var meteorStrikePeriodicSkillContainerEntity = GetEntity(authoring.meteorStrikeContainerGameObjectPrefab,
                TransformUsageFlags.None);
            var lightningStormVFXEntity =
                GetEntity(authoring.lightningStormGameObjectPrefab, TransformUsageFlags.Dynamic);
            var lightningStormPeriodicSkillContainerEntity =
                GetEntity(authoring.lightningStormContainerGameObjectPrefab, TransformUsageFlags.None);
            var lightningStormNoDamageVFXEntity = GetEntity(authoring.lightningStormNoDamageGameObjectPrefab,
                TransformUsageFlags.Dynamic);
            var lightningStormNoDamagePeriodicSkillContainerEntity =
                GetEntity(authoring.lightningStormNoDamageContainerGameObjectPrefab, TransformUsageFlags.None);

            // final assembly
            AddComponent(spawnerEntity, new SkillSpawnerPrefabs
            {
                // skill
                BlazingTrailPeriodicSkillContainerEntity = blazingTrailPeriodicSkillContainerEntity,
                BlazingTrailVFXEntityPrefab = blazingTrailVFXEntity,
                SmallTornadoMovableSkillContainerEntity = tornadoMovableSkillContainerEntity,
                SmallTornadoVFXEntityPrefab = tornadoVFXEntity,
                WhirlPoolPeriodicSkillContainerEntity = whirlPoolPeriodicSkillContainerEntity,
                WhirlPoolVFXEntityPrefab = whirlPoolVFXEntity,
                ChainLightningVFXEntityPrefab = chainLightningVFXEntity,
                ChainLightningCollisionEntityPrefab = chainLightningCollisionEntity,

                // trigger explosion skill
                ElementConflictExplosionPeriodicSkillContainerEntity =
                    elementConflictExplosionPeriodicSkillContainerEntity,
                ElementConflictExplosionVFXEntityPrefab = elementConflictExplosionVFXEntity,
                BlazingLavaPeriodicSkillContainerEntity = blazingLavaPeriodicSkillContainerEntity,
                BlazingLavaVFXEntityPrefab = blazingLavaVFXEntity,
                FireTornadoMovableSkillContainerEntity = fireTornadoMovableSkillContainerEntity,
                FireTornadoVFXEntityPrefab = fireTornadoVFXEntity,
                WindTornadoMovableSkillContainerEntity = windTornadoMovableSkillContainerEntity,
                WindTornadoVFXEntityPrefab = windTornadoVFXEntity,
                WaterTornadoMovableSkillContainerEntity = waterTornadoMovableSkillContainerEntity,
                WaterTornadoVFXEntityPrefab = waterTornadoVFXEntity,
                BigPoolPeriodicSkillContainerEntity = bigPoolPeriodicSkillContainerEntity,
                BigPoolVFXEntityPrefab = bigPoolVFXEntity,
                LightningStrikeWaterPeriodicSkillContainerEntity = lightningStrikeWaterPeriodicSkillContainerEntity,
                LightningStrikeWaterVFXEntityPrefab = lightningStrikeWaterVFXEntity,
                FireFromLightningPeriodicSkillContainerEntity = fireFromLightningPeriodicSkillContainerEntity,
                FireFromLightningVFXEntityPrefab = fireFromLightningVFXEntity,

                // Big VFX - when triggered ppm of one element >= threshold
                SmallTsunamiMovableSkillContainerEntity = smallTsunamiMovableSkillContainerEntity,
                SmallTsunamiVFXEntityPrefab = smallTsunamiVFXEntity,
                GaleBladeStormMovableSkillContainerEntity = galeBladeStormMovableSkillContainerEntity,
                GaleBladeStormVFXEntityPrefab = galeBladeStormVFXEntity,
                BigMeteorStrikePeriodicSkillContainerEntity = bigMeteorStrikePeriodicSkillContainerEntity,
                BigMeteorStrikeVFXEntityPrefab = bigMeteorStrikeVFXEntity,

                // auto explosion skill
                TsunamiMovableSkillContainerEntity = tsunamiPeriodicSkillContainerEntity,
                TsunamiVFXEntityPrefab = tsunamiVFXEntity,
                SuperTornadoMovableSkillContainerEntity = superTornadoMovableSkillContainerEntity,
                SuperTornadoVFXEntityPrefab = superTornadoVFXEntity,
                MeteorStrikePeriodicSkillContainerEntity = meteorStrikePeriodicSkillContainerEntity,
                MeteorStrikeVFXEntityPrefab = meteorStrikeVFXEntity,
                LightningStormPeriodicSkillContainerEntity = lightningStormPeriodicSkillContainerEntity,
                LightningStormVFXEntityPrefab = lightningStormVFXEntity,
                LightningStormNoDamagePeriodicSkillContainerEntity = lightningStormNoDamagePeriodicSkillContainerEntity,
                LightningStormNoDamageVFXEntityPrefab = lightningStormNoDamageVFXEntity
            });
        }
    }

    [WorldSystemFilter(WorldSystemFilterFlags.BakingSystem)]
    internal partial struct SkillBakingSystem : ISystem, ISystemStartStop
    {
        public void OnCreate(ref SystemState state)
        {
            state.RequireForUpdate<SkillSpawnerPrefabs>();
        }

        public void OnStartRunning(ref SystemState state)
        {
            var skillPrefabContainer = SystemAPI.GetSingletonEntity<SkillSpawnerPrefabs>();
            var skillSpawnerPrefabs = state.EntityManager.GetComponentData<SkillSpawnerPrefabs>(skillPrefabContainer);

            #region Blazing Trail

            // Blazing trail - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.BlazingTrailVFXEntityPrefab);
            // fade in/out
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailVFXEntityPrefab,
                new SkillElementVFXFadeFactorsData
                {
                    CurrentLiveTime = 0,
                    TimeToReduce = Constants.BlazingTrailVFXTimeToReduce,
                    CutOutFactorTime = 0,
                    CutOutFactorDuration = Constants.BlazingTrailVFXFadeOutDuration,
                    UpFactorTime = 0,
                    UpFactorDuration = Constants.BlazingTrailVFXFadeInDuration,
                    IsUpFactor = true
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.BlazingTrailPeriodicDamageInterval,
                    DamageValue = Constants.BlazingTrailDamage,
                    Element = ElementEnum.Fire
                });

            // Blazing trail - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.BlazingTrail,
                    Ppm = Constants.BlazingTrailPpm,
                    ResidueRadius = Constants.BlazingTrailResidueRadius,
                    CreateResidue = true,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .BlazingTrailVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.BlazingTrailVFXEntityPrefab,
                    ResidueDelay = Constants.BlazingTrailResidueDelay,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = Constants.BlazingTrailPeriodicSkillContainerSpawnInterval,
                    SpawnCount = 0,
                    MaxSpawnCount = Constants.BlazingTrailPeriodicSkillContainerMaxSpawnCount
                });
            // track player
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailPeriodicSkillContainerEntity,
                new SkillTrackedData
                {
                    Target = Entity.Null
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingTrailPeriodicSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Small Tornado

            // Tornado - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab, new WhirlTag
            {
                WhirlSpeed = Constants.TornadoAttractSpeed
            });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.SmallTornadoDamage,
                    Element = ElementEnum.Wind
                });
            // Tornado - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Wind,
                    Skill = SkillEnum.SmallTornado,
                    Ppm = Constants.SmallTornadoPpm,
                    ResidueRadius = Constants.SmallTornadoResidueRadius,
                    CreateResidue = true,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .SmallTornadoVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.SmallTornadoVFXEntityPrefab,
                    ResidueDelay = Constants.SmallTornadoResidueDelay,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.SmallTornadoSpeed,
                    MaxLiveTime = Constants.SmallTornadoLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTornadoMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Whirl Pool

            // Whirl Pool - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.WhirlPoolLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.WhirlPoolPeriodicDamageInterval,
                    DamageValue = Constants.WhirlPoolDamage,
                    Element = ElementEnum.Water
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab, new WhirlTag
            {
                WhirlSpeed = Constants.WhirlPoolAttractSpeed
            });

            // Whirl Pool - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Water,
                    Skill = SkillEnum.WhirlPool,
                    Ppm = Constants.WhirlPoolPpm,
                    ResidueRadius = Constants.WhirlPoolResidueRadius,
                    CreateResidue = true,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .WhirlPoolVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.WhirlPoolVFXEntityPrefab,
                    ResidueDelay = Constants.WhirlPoolResidueDelay,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WhirlPoolPeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Chain Lightning

            // Chain Lightning - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ChainLightningVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ChainLightningVFXEntityPrefab,
                new ChainLightningData());
            state.EntityManager.AddBuffer<ChainLightningHit>(skillSpawnerPrefabs.ChainLightningVFXEntityPrefab);

            // Chain Lightning - Collision Entity
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ChainLightningCollisionEntityPrefab,
                new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.ChainLightningCollisionEntityPrefab);
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ChainLightningCollisionEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.ChainLightningDamage,
                    Element = ElementEnum.Lightning
                });

            #endregion

            #region Element Conflict Explosion

            // Element Conflict Explosion - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ElementConflictExplosionVFXEntityPrefab,
                new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.ElementConflictExplosionVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ElementConflictExplosionVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.ElementConflictExplosionLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.ElementConflictExplosionVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DelayTime = Constants.ElementConflictExplosionDelayTime,
                    HasDelayTime = 0,
                    DamageValue = Constants.ElementConflictExplosionDamage,
                    Element = ElementEnum.TrueDamage
                });
            // Element Conflict Explosion - Periodic skill container
            state.EntityManager.AddComponentData(
                skillSpawnerPrefabs.ElementConflictExplosionPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(
                skillSpawnerPrefabs.ElementConflictExplosionPeriodicSkillContainerEntity, new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.ElementConflictExplosion,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .ElementConflictExplosionVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.ElementConflictExplosionVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(
                skillSpawnerPrefabs.ElementConflictExplosionPeriodicSkillContainerEntity, new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(
                skillSpawnerPrefabs.ElementConflictExplosionPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(
                skillSpawnerPrefabs.ElementConflictExplosionPeriodicSkillContainerEntity, new StillPositionData());

            #endregion

            #region Blazing Lava

            // Blazing Lava - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.BlazingLavaVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.BlazingLavaLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.BlazingLavaPeriodicDamageInterval,
                    DamageValue = Constants.BlazingLavaDamage,
                    Element = ElementEnum.Fire
                });
            // Blazing Lava - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.BlazingLava,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .BlazingLavaVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.BlazingLavaVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BlazingLavaPeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Fire Tornado

            // Fire Tornado - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.FireTornadoVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoVFXEntityPrefab, new WhirlTag
            {
                WhirlSpeed = Constants.TornadoAttractSpeed
            });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.ElementTornadoDamage,
                    Element = ElementEnum.Fire
                });
            // Fire Tornado - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.FireTornado,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .FireTornadoVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.FireTornadoVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.ElementTornadoSpeed,
                    MaxLiveTime = Constants.ElementTornadoLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireTornadoMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Wind Tornado

            // Wind Tornado - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.WindTornadoVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoVFXEntityPrefab, new WhirlTag
            {
                WhirlSpeed = Constants.TornadoAttractSpeed
            });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.ElementTornadoDamage,
                    Element = ElementEnum.Wind
                });
            // Wind Tornado - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Wind,
                    Skill = SkillEnum.WindTornado,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .WindTornadoVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.WindTornadoVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.ElementTornadoSpeed,
                    MaxLiveTime = Constants.ElementTornadoLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WindTornadoMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Water Tornado

            // Water Tornado - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab, new WhirlTag
            {
                WhirlSpeed = Constants.TornadoAttractSpeed
            });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.ElementTornadoDamage,
                    Element = ElementEnum.Water
                });

            // Water Tornado - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Water,
                    Skill = SkillEnum.WaterTornado,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .WaterTornadoVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.WaterTornadoVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.ElementTornadoSpeed,
                    MaxLiveTime = Constants.ElementTornadoLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.WaterTornadoMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Big Pool

            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.BigPoolVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.BigPoolLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.BigPoolPeriodicDamageInterval,
                    DamageValue = Constants.BigPoolDamage,
                    Element = ElementEnum.Water
                });

            // Big Pool - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Water,
                    Skill = SkillEnum.BigPool,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .BigPoolVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.BigPoolVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigPoolPeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Big Chain Lightning

            // it uses same as Chain Lightning, but it's complex scriptable skill

            #endregion

            #region Lightning Strike Water

            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterVFXEntityPrefab,
                new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.LightningStrikeWaterVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.LightningStrikeWaterLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.LightningStrikeWaterPeriodicDamageInterval,
                    DamageValue = Constants.LightningStrikeWaterDamage,
                    Element = ElementEnum.Lightning
                });

            // Lightning Strike Water - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Lightning,
                    Skill = SkillEnum.LightningStrikeWater,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .LightningStrikeWaterVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.LightningStrikeWaterVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStrikeWaterPeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Fire From Lightning

            // Fire From Lightning - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningVFXEntityPrefab,
                new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.FireFromLightningVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.FireFromLightningLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    PeriodicTime = Constants.FireFromLightningPeriodicDamageInterval,
                    DamageValue = Constants.FireFromLightningDamage,
                    Element = ElementEnum.Fire
                });
            // Fire From Lightning - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.FireFromLightning,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .FireFromLightningVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.FireFromLightningVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            // scalable
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.FireFromLightningPeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Small Tsunami

            // Small Tsunami - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.SmallTsunamiVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.SmallTsunamiDamage,
                    Element = ElementEnum.Water
                });

            // Small Tsunami - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Water,
                    Skill = SkillEnum.SmallTsunami,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .SmallTsunamiVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.SmallTsunamiVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.SmallTsunamiSpeed,
                    MaxLiveTime = Constants.SmallTsunamiLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SmallTsunamiMovableSkillContainerEntity,
                new SkillContainerScalableData());

            //TODO: 添加对怪物的控制技能，推到指定位置。

            #endregion

            #region Gale Blade Storm

            // Gale Blade Storm - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.GaleBladeStormVFXEntityPrefab);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectValueDamage,
                    DamageValue = Constants.GaleBladeStormDamage,
                    Element = ElementEnum.Wind
                });

            // Gale Blade Storm - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormMovableSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Wind,
                    Skill = SkillEnum.GaleBladeStorm,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .GaleBladeStormVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.GaleBladeStormVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.GaleBladeStormSpeed,
                    MaxLiveTime = Constants.GaleBladeStormLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.GaleBladeStormMovableSkillContainerEntity,
                new SkillContainerScalableData());

            // TODO: 添加轻推一下怪物的技能效果

            #endregion

            #region Big Meteor Strike

            // Big Meteor Strike - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikeVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddBuffer<HitList>(skillSpawnerPrefabs.BigMeteorStrikeVFXEntityPrefab);
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikeVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.BigMeteorStrikeVFXElementLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikeVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.PeriodicValueDamage,
                    DelayTime = Constants.BigMeteorStrikeDelayTime,
                    HasDelayTime = 0,
                    PeriodicTime = Constants.BigMeteorStrikePeriodicDamageInterval,
                    DamageValue = Constants.BigMeteorStrikeDamage,
                    Element = ElementEnum.Fire
                });

            // Big Meteor Strike - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikePeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikePeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.BigMeteorStrike,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .BigMeteorStrikeVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.BigMeteorStrikeVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikePeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = 1,
                    SpawnCount = 0,
                    MaxSpawnCount = 1
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikePeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            // position control
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.BigMeteorStrikePeriodicSkillContainerEntity,
                new StillPositionData());

            #endregion

            #region Chain Lightning Rampage

            // it uses same as Chain Lightning, but it's complex scriptable skill

            #endregion

            #region Tsunami

            // Tsunami - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiVFXEntityPrefab, new AutoExplosionTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectPercentageDamage,
                    DamageValue = Constants.TsunamiDamage,
                    Element = ElementEnum.Water
                });
            // Tsunami - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Water,
                    Skill = SkillEnum.Tsunami,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .TsunamiVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.TsunamiVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.TsunamiSpeed,
                    MaxLiveTime = Constants.TsunamiLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.TsunamiMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Super Tornado

            // Super Tornado - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoVFXEntityPrefab,
                new AutoExplosionTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoVFXEntityPrefab,
                new SkillElementVFXMobilityData());
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectPercentageDamage,
                    DamageValue = Constants.SuperTornadoDamage,
                    Element = ElementEnum.Wind
                });
            // Super Tornado - Movable skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoMovableSkillContainerEntity,
                new MovableSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoMovableSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Wind,
                    Skill = SkillEnum.SuperTornado,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .SuperTornadoVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.SuperTornadoVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoMovableSkillContainerEntity,
                new MovableSkillContainerData
                {
                    StartPosition = float3.zero,
                    NormalizedDirection = float3.zero,
                    Speed = Constants.SuperTornadoSpeed,
                    MaxLiveTime = Constants.SuperTornadoLifeTime
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.SuperTornadoMovableSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Meteor Strike

            // Meteor Strike - VFX
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikeVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikeVFXEntityPrefab,
                new AutoExplosionTag());
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikeVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.MeteorStrikeVFXElementLifeTime,
                    ElapsedLifetime = 0
                });
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikeVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectPercentageDamage,
                    DelayTime = Constants.MeteorStrikeDelayTime,
                    HasDelayTime = 0,
                    DamageValue = Constants.MeteorStrikeDamage,
                    Element = ElementEnum.Fire
                });

            // Meteor Strike - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikePeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikePeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Fire,
                    Skill = SkillEnum.MeteorStrike,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .MeteorStrikeVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.MeteorStrikeVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            // position control
            var spawnCountMeteorStrike = AddFullMapAttackPosition(ref state,
                skillSpawnerPrefabs.MeteorStrikePeriodicSkillContainerEntity, Constants.MeteorStrikeSideOfEachSkill,
                Constants.MeteorStrikeYPosition);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikePeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = Constants.MeteorStrikeSpawnInterval,
                    SpawnCount = 0,
                    MaxSpawnCount = spawnCountMeteorStrike
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.MeteorStrikePeriodicSkillContainerEntity,
                new SkillContainerScalableData());

            #endregion

            #region Lightning Storm

            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormVFXEntityPrefab, new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormVFXEntityPrefab,
                new AutoExplosionTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamageVFXEntityPrefab,
                new SkillVFXTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamageVFXEntityPrefab,
                new AutoExplosionTag());
            // damage
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormVFXEntityPrefab,
                new SkillElementVFXDamageData
                {
                    DamageType = DamageTypeEnum.DirectPercentageDamage,
                    DamageValue = Constants.LightningStormDamage,
                    Element = ElementEnum.Lightning
                });
            // still data
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.LightningStormVFXElementLifeTime,
                    ElapsedLifetime = 0
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamageVFXEntityPrefab,
                new SkillElementVFXStillData
                {
                    MaxLiveTime = Constants.LightningStormVFXElementLifeTime,
                    ElapsedLifetime = 0
                });

            // Lightning Storm - Periodic skill container
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormPeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamagePeriodicSkillContainerEntity,
                new PeriodicSkillContainerTag());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormPeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Lightning,
                    Skill = SkillEnum.LightningStorm,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .LightningStormVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.LightningStormVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamagePeriodicSkillContainerEntity,
                new SkillContainerData
                {
                    Element = ElementEnum.Lightning,
                    Skill = SkillEnum.LightningStorm,
                    Ppm = 0,
                    ResidueRadius = 0,
                    CreateResidue = false,
                    VfxPrefabTransform =
                        state.EntityManager.GetComponentData<LocalTransform>(skillSpawnerPrefabs
                            .LightningStormNoDamageVFXEntityPrefab),
                    SkillElementPrefab = skillSpawnerPrefabs.LightningStormNoDamageVFXEntityPrefab,
                    ResidueDelay = 0,
                    ResidueParentEntity = Entity.Null
                });
            // position control
            var spawnCountLightningStorm = AddFullMapAttackPosition(ref state,
                skillSpawnerPrefabs.LightningStormPeriodicSkillContainerEntity, Constants.LightningStormSideOfEachSkill,
                Constants.LightningStormYPosition);
            var spawnCountLightningStormNoDamage = RandomFullMapAttackPosition(ref state,
                skillSpawnerPrefabs.LightningStormNoDamagePeriodicSkillContainerEntity,
                Constants.LightningStormSideOfEachSkill, Constants.LightningStormYPosition);
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormPeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = Constants.LightningStormSpawnInterval,
                    SpawnCount = 0,
                    MaxSpawnCount = spawnCountLightningStorm
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamagePeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = Constants.LightningStormNoDamageSpawnInterval,
                    SpawnCount = 0,
                    MaxSpawnCount = spawnCountLightningStormNoDamage
                });
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormPeriodicSkillContainerEntity,
                new SkillContainerScalableData());
            state.EntityManager.AddComponentData(skillSpawnerPrefabs.LightningStormNoDamagePeriodicSkillContainerEntity,
                new PeriodicSkillContainerData
                {
                    LastSpawnTime = 0,
                    SpawnInterval = Constants.LightningStormSpawnInterval,
                    SpawnCount = 0,
                    MaxSpawnCount = spawnCountLightningStorm
                });

            #endregion
        }

        public void OnStopRunning(ref SystemState state)
        {
        }

        private int AddFullMapAttackPosition(ref SystemState state, Entity entity, float sideOfEachSkill,
            float attackYPosition)
        {
            // calculate all place to put the skill
            var totalAttack = (int)math.ceil((Constants.MapRight - Constants.MapLeft) / sideOfEachSkill *
                (Constants.MapTop - Constants.MapBottom) / sideOfEachSkill);
            var positions = new float3[totalAttack];

            var index = 0;
            for (var x = Constants.MapLeft + sideOfEachSkill / 2; x < Constants.MapRight; x += sideOfEachSkill)
            for (var z = Constants.MapBottom + sideOfEachSkill / 2; z < Constants.MapTop; z += sideOfEachSkill)
            {
                positions[index] = new float3(x, attackYPosition, z);
                index++;
            }

            // random sequence - Fisher-Yates shuffle
            for (var i = positions.Length - 1; i > 0; i--)
            {
                var randomIndex = Random.Range(0, i + 1);
                (positions[i], positions[randomIndex]) = (positions[randomIndex], positions[i]);
            }

            var attackDataBuffer = state.EntityManager.AddBuffer<PeriodicNextAttackData>(entity);
            attackDataBuffer.ResizeUninitialized(totalAttack);
            for (var i = 0; i < totalAttack; i++)
                attackDataBuffer[i] = new PeriodicNextAttackData
                {
                    Position = positions[i]
                };
            return totalAttack;
        }

        private int RandomFullMapAttackPosition(ref SystemState state, Entity entity, float sideOfEachSkill,
            float attackYPosition)
        {
            // Estimate the number of attacks based on the map size and desired spacing
            var totalAttack = (int)math.ceil((Constants.MapRight - Constants.MapLeft) / sideOfEachSkill *
                (Constants.MapTop - Constants.MapBottom) / sideOfEachSkill);

            var positions = new float3[totalAttack];

            for (var i = 0; i < totalAttack; i++)
            {
                // Use noise to add variation to position
                var noiseX = Mathf.PerlinNoise(Random.value * 100, 0) * (Constants.MapRight - Constants.MapLeft) +
                             Constants.MapLeft;
                var noiseZ = Mathf.PerlinNoise(0, Random.value * 100) * (Constants.MapTop - Constants.MapBottom) +
                             Constants.MapBottom;

                // Adjust position based on noise and random offsets within each cell
                var x = noiseX + Random.Range(-sideOfEachSkill / 2, sideOfEachSkill / 2);
                var z = noiseZ + Random.Range(-sideOfEachSkill / 2, sideOfEachSkill / 2);

                // Ensure positions are within map boundaries
                x = Mathf.Clamp(x, Constants.MapLeft, Constants.MapRight);
                z = Mathf.Clamp(z, Constants.MapBottom, Constants.MapTop);

                positions[i] = new float3(x, attackYPosition, z);
            }

            // Add these positions to the entity as buffer elements
            var attackDataBuffer = state.EntityManager.AddBuffer<PeriodicNextAttackData>(entity);
            attackDataBuffer.ResizeUninitialized(totalAttack);
            for (var i = 0; i < totalAttack; i++)
                attackDataBuffer[i] = new PeriodicNextAttackData
                {
                    Position = positions[i]
                };

            return totalAttack;
        }
    }
}
```