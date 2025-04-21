# IJobEntity

example:

```csharp
using Unity.Entities;
using Unity.Mathematics;
using Zoo.Yifei.Scripts.Achievement;
using Zoo.Yifei.Scripts.Audio;
using Zoo.Yifei.Scripts.Camera;
using Zoo.Yifei.Scripts.Enums;

namespace Zoo.Yifei.Scripts.Skill.TriggerSkill
{
    public partial struct TriggerWaterTornadoJob : IJobEntity, ITriggerSkill
    {
        public EntityCommandBuffer.ParallelWriter Ecb { get; set; }
        public float3 StartPosition { get; set; }
        public float3 Direction { get; set; }
        public float Radius { get; set; }

        public void Execute([ChunkIndexInQuery] int chunkIndex, in SkillSpawnerPrefabs skillSpawnerPrefabs)
        {
            SkillAudioManager.Instance.PlayAudioByEnumAndPos(SkillAudioClipIndex.Tsunami, new float3(0, 0, 0));
            ImpulseController.Instance.GenerateImpulse(StartPosition, Direction, 0.2f,
                (float)Constants.ElementTornadoLifeTime);
            AchievementManager.Instance.UnlockAchievement(SkillEnum.WaterTornado);
            var waterTornadoContainer =
                Ecb.Instantiate(chunkIndex, skillSpawnerPrefabs.WaterTornadoMovableSkillContainerEntity);
            Ecb.SetComponent(chunkIndex, waterTornadoContainer, new MovableSkillContainerData
            {
                StartPosition = StartPosition,
                NormalizedDirection = math.normalizesafe(Direction, new float3(0, 0, 0)),
                Speed = Constants.ElementTornadoSpeed,
                MaxLiveTime = Constants.ElementTornadoLifeTime
            });
            // it is big enough, no need to scale to two residues
            // Ecb.SetComponent(chunkIndex, waterTornadoContainer, new SkillContainerScalableData
            // {
            //     Scale = Radius / Constants.ElementTornadoScaleToRadiusFactor,
            //     ChangeScale = true
            // });
        }
    }
}
```