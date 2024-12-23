# Mongo_Operations

1. [basic query + aggregation](#basic-query--aggregation)
   1. [Task Example](#task-example)
2. [Distribution](#distribution)
   1. [replication](#replication)
      1. [non-vote一次只能设置一个节点为non-vote](#non-vote一次只能设置一个节点为non-vote)
   2. [Sharding](#sharding)
      1. [moveChunk](#movechunk)
      2. [mongos](#mongos)
      3. [Task Example](#task-example-1)
         1. [启动](#启动)
         2. [配置router（mongos进程）](#配置routermongos进程)
         3. [配置replication](#配置replication)
         4. [开始使用](#开始使用)
         5. [result](#result)
3. [project - logistic system](#project---logistic-system)
   1. [Nodes setting](#nodes-setting)
      1. [start servers](#start-servers)
      2. [initiate configure server and shard server](#initiate-configure-server-and-shard-server)
      3. [start router](#start-router)
      4. [add replication nodes](#add-replication-nodes)
         1. [shard1](#shard1)
         2. [shard2](#shard2)
   2. [set range shard of one collection](#set-range-shard-of-one-collection)
   3. [Create documents](#create-documents)
      1. [collection - packages](#collection---packages)
   4. [query:](#query)


## basic query + aggregation
[Basic](MongoDB_lab1.pdf)
[Aggregation](MongoDB_lab2.pdf)


### Task Example
1. Tasks
```
For collection "cities" write queries (note that connections between cities are unidirectional):

1. find the distance from Kałużów to Pacynków,
2. add a connection from Pacynków to Pacynków with a distance of 40,
3. calculate a combined population of cities reachable from Pacynków.

For collection "albums" write queries:

1. find artists that had "Big Bad" as a guest,
2. add "Bonjo" as a guest artist in the track "100m",
3. calculate the combined length of the tracks performed by "Bonjo" (both his as well as guest performances).
```
2.  Data:
* "cities" collection:
```BSON
{
 city: "Arnoldów",
 population: 345,
 reachable_from:
 [
  {city: "Arnoldów", distance:34},
  {city: "Kałużów", distance:2}
 ]
},
{
 city: "Pacynków",
 population: 2,
 reachable_from:
 [
  {city: "Arnoldów", distance:5},
  {city: "Kałużów", distance:17},
  {city: "Mrzawków", distance:4}
 ]
},
{
 city: "Kałużów",
 population: 100000,
 reachable_from:
 [
  {city: "Mrzawków", distance: 12},
  {city: "Pacynków", distance: 23}
 ]
},
{
 city: "Mrzawków",
 population: 6727,
 reachable_from:
 [
  {city: "Pacynków", distance:11}
 ]
}
```
* "albums" collection:
```BSON
{
 artist: "Bonjo",
 album: "Banjo",
 tracks:
 [
  {title: "bip", length: 3.45},
  {title: "bop", length: 2.17, guest: "Rock"},
  {title: "bap", length: 4.05, guest: "Short"}
 ]
},
{
 artist: "Rock",
 album: "Roll",
 tracks:
 [
  {title: "Jail", length: 4.56, guest: "Big Bad"},
  {title: "House", length: 8.97},
  {title: "Rock", length: 2.34}
 ]
},
{
 artist: "Big Bad",
 album: "Wolf",
 tracks:
 [
  {title: "Little", length: 1.11, guest: "Bonjo"},
  {title: "Red", length: 2.77},
  {title: "Riding", length: 5.13},
  {title: "Hood", length: 4.05}
 ]
},
{
 artist: "Short",
 album: "Track",
 tracks:
 [
  {title: "100m", length: 10.00},
  {title: "200m", length: 20.00, guest: "Big Bad"}
 ]
}
```
3. Queris:
**Task1:**
  1. find the distance from Kałużów to Pacynków,
    ```bash
    test> db.cities.find({city:"Pacynków","reachable_from.city":"Kałużów"},{_id:0,city:1,"reachable_from.$":1})
    [
      {
        city: 'Pacynków',
        reachable_from: [ { city: 'Kałużów', distance: 17 } ]
      }
    ]
    ```
  2. add a connection from Pacynków to Pacynków with a distance of 40
   ```bash
   test> db.cities.updateOne({city:"Pacynków"},{$push:{"reachable_from":{city:"Pacynków", distance:40}}})
   {
     acknowledged: true,
     insertedId: null,
     matchedCount: 1,
     modifiedCount: 1,
     upsertedCount: 0
   }
   ```
  3. calculate a combined population of cities reachable from Pacynków.
    ```bash
    test> db.cities.aggregate([{$unwind:"$reachable_from"},{$group:{_id:"$reachable_from.city",sum_pop:{$sum:"$population"}}},{$match:{_id:"Pacynków"}}])
    [ { _id: 'Pacynków', sum_pop: 106729 } ]
    ```
**Task2:**
  1. find artists that had "Big Bad" as a guest,
   ```bash
   test> db.albums.find({"tracks.guest":"Big Bad"},{_id:0, artist:1})
   [ { artist: 'Rock' }, { artist: 'Short' } ]
   ```
  2. add "Bonjo" as a guest artist in the track "100m",
   ```bash
   test> db.albums.updateMany({"tracks.title":"100m"},{$set:{"tracks.$[modify].guest":"Bonjo"}},{arrayFilters:[{"modify.title":"100m"}]})
   {
     acknowledged: true,
     insertedId: null,
     matchedCount: 1,
     modifiedCount: 1,
     upsertedCount: 0
   }
   ```
  3. calculate the combined length of the tracks performed by "Bonjo" (both his as well as guest performances).
   ```bash
   test> db.albums.aggregate([{$unwind:"$tracks"},{$match:{$or:[{artist: 'Bonjo'},{"tracks.guest":"Bonjo"}]}},{$group:{_id:"total",sumLen:{$sum:"$tracks.length"}}}])
   [ { _id: 'total', sumLen: 20.78 } ]
   ```
  
## Distribution

### replication
[replication](MongoDB_Dist_lab1.pdf)

```cmd
start cmd /K mongod --port 27017 --dbpath .\data_dbs\db1 --replSet replicaSet
timeout /T 5
start cmd /K mongod --port 27018 --dbpath .\data_dbs\db2 --replSet replicaSet
timeout /T 5
start cmd /K mongod --port 27019 --dbpath .\data_dbs\db3 --replSet replicaSet
timeout /T 5
start cmd /K mongod --port 27020 --dbpath .\data_dbs\db4 --replSet replicaSet
timeout /T 5
start cmd /K mongod --port 27021 --dbpath .\data_dbs\db5 --replSet replicaSet
timeout /T 5
start cmd /K mongosh --host "127.0.0.1:27017"
```

#### non-vote一次只能设置一个节点为non-vote
否则会报错

```bash
rs.initiate()
rs.add('127.0.0.1:27018')
# ...相似操作...
# 将默认读 concern从maority改为1，这样可以添加arbiter
db.adminCommand({setDefaultRWConcern:1, defaultWriteConcern: {w:1}})
rs.addArb('127.0.0.1:27019')
cfg=rs.conf()
cfg.members[3].votes=0 
rs.reconfig(cfg) 
cfg.members[4].votes=0 
rs.reconfig(cfg)
```

### Sharding
[sharding](MongoDB_Dist_lab2.pdf)

#### moveChunk
```bash
sh.startBalancer()
# 上一条不一定有效，下一条强制移动
sh.moveChunk("ourBase.col1", {a:'eee', b:'ffff'}, 'shard1Set')
```

#### mongos
mongos进程：
一个或多个配置服务器均处于运行状态后，启动一个mongos进程供应用程序连接。mongos进程需要配置服务器的地址，所以必须使用--configdb选项启动mongos:
`mongos --configdb config-1:27019,config-2:27019,config-3:27019 -f /var/lib/mongos.conf`
* 默认情况下，mongos运行在27017端口。mongos本身不保存数据，它会在启动时从配置服务器加载集群数据。
* 可以启动任意数量的mongos进程。通常的设置时每个应用程序服务器使用一个mongos进程(与应用服务器运行在同一台机器上)
* 每个mongos进程必须按照列表排序，使用相同的配置服务器列表。

#### Task Example
创建一个有 3 个分片的分片集群，使主分片有一个副本和一个仲裁者。
创建 3 个集合，保留一个未分片，在非默认分片之间分配一个，第三个使用散列分片进行分配。

##### 启动
**下面启动命令中17是configure server，16是router**

```cmd
start cmd /K mongod --configsvr --port 27017 --dbpath .\data_dbs\config --replSet replicaSet
timeout /T 5
start cmd /K mongod --shardsvr --port 27018 --dbpath .\data_dbs\db1 --replSet replicaSet
timeout /T 5
start cmd /K mongod --shardsvr --port 27019 --dbpath .\data_dbs\db2 --replSet replicaSet
timeout /T 5
start cmd /K mongod --shardsvr --port 27020 --dbpath .\data_dbs\db3 --replSet replicaSet
timeout /T 5
start cmd /K mongod --port 27021 --dbpath .\data_dbs\db4 --replSet shard1Set
timeout /T 5
start cmd /K mongod --port 27022 --dbpath .\data_dbs\db5 --replSet shard1Set
timeout /T 5
start cmd /K mongos --configdb confSet/127.0.0.1:27017 --port 27016
timeout /T 5
start cmd /K mongosh --port 27017
start cmd /K mongosh --port 27018
start cmd /K mongosh --port 27019
start cmd /K mongosh --port 27020
```

**`start cmd /K mongosh --port 27016`这时启动会失败**

```bash
rs.initiate({_id:"confSet", configsvr: true, members: [{_id: 0, host: "127.0.0.1:27017"}]})
rs.initiate( { _id: "shard1Set", members: [ { _id: 0, host: "127.0.0.1:27018"}]})
rs.initiate( { _id: "shard2Set", members: [ { _id: 0, host: "127.0.0.1:27019"}]})
rs.initiate( { _id: "shard3Set", members: [ { _id: 0, host: "127.0.0.1:27020"}]})
```

现在再启动27016
```cmd
mongosh --port 27016
```

##### 配置router（mongos进程）
```bash
sh.addShard("shard1Set/127.0.0.1:27018")
sh.addShard("shard2Set/127.0.0.1:27019")
sh.addShard("shard3Set/127.0.0.1:27020")
sh.enableSharding("ourBase")
```

##### 配置replication
在mongos进程中用`sh.status()`查看primary shard

在primary shard中：
```bash
rs.add('127.0.0.1:27021')
db.adminCommand({setDefaultRWConcern:1, defaultWriteConcern: {w:1}})
```

分片不能使用setDefaultRWConcern，所以在router上修改：

```bash
db.adminCommand({setDefaultRWConcern:1, defaultWriteConcern: {w:1}})
```

回到primary shard：
```bash
rs.addArb('127.0.0.1:27022')
```

##### 开始使用
在mongos进程中：
```bash
use ourBase
```

```bash
db.col_unshard.insertOne({a:1, b:1})
db.col_unshard.insertOne({a:2, b:2})
db.col_unshard.insertOne({a:3, b:3})
db.col_unshard.insertOne({a:4, b:4})
db.col_unshard.insertOne({a:5, b:5})
db.col_unshard.insertOne({a:6, b:6})

sh.shardCollection("ourBase.col", {a: 1})
sh.splitAt("ourBase.col", {a: 'c'})
sh.splitAt("ourBase.col", {a: 'e'})
sh.moveChunk("ourBase.col", {a:'c'}, 'shard2Set')
sh.moveChunk("ourBase.col", {a:'e'}, 'shard3Set')
db.col.insertOne({a:'a', b:1})
db.col.insertOne({a:'b', b:2})
db.col.insertOne({a:'c', b:3})
db.col.insertOne({a:'d', b:4})
db.col.insertOne({a:'e', b:5})
db.col.insertOne({a:'f', b:6})

sh.shardCollection("ourBase.col_hash", {a: "hashed"})
db.col_hash.insertOne({a:'a'})
db.col_hash.insertOne({a:'b'})
db.col_hash.insertOne({a:'c'})
db.col_hash.insertOne({a:'d'})
db.col_hash.insertOne({a:'e'})
db.col_hash.insertOne({a:'f'})
db.col_hash.insertOne({a:'g'})
db.col_hash.insertOne({a:'h'})
db.col_hash.insertOne({a:'i'})
db.col_hash.insertOne({a:'j'})
db.col_hash.insertOne({a:'k'})
db.col_hash.insertOne({a:'l'})
db.col_hash.insertOne({a:'m'})
db.col_hash.insertOne({a:'n'})
db.col_hash.insertOne({a:'o'})
db.col_hash.insertOne({a:'p'})
db.col_hash.insertOne({a:'q'})
db.col_hash.insertOne({a:'r'})
db.col_hash.insertOne({a:'s'})
db.col_hash.insertOne({a:'t'})
db.col_hash.insertOne({a:'u'})
db.col_hash.insertOne({a:'v'})
db.col_hash.insertOne({a:'w'})
db.col_hash.insertOne({a:'x'})
db.col_hash.insertOne({a:'y'})
db.col_hash.insertOne({a:'z'})
```

##### result
```bash
[direct: mongos] ourBase> sh.status()
shardingVersion
{
  _id: 1,
  minCompatibleVersion: 5,
  currentVersion: 6,
  clusterId: ObjectId("63ab5f91a2203f557b4c8999")
}
---
shards
[
  {
    _id: 'shard1Set',
    host: 'shard1Set/127.0.0.1:27018,127.0.0.1:27021',
    state: 1,
    topologyTime: Timestamp({ t: 1672180637, i: 3 })
  },
  {
    _id: 'shard2Set',
    host: 'shard2Set/127.0.0.1:27019',
    state: 1,
    topologyTime: Timestamp({ t: 1672180643, i: 5 })
  },
  {
    _id: 'shard3Set',
    host: 'shard3Set/127.0.0.1:27020',
    state: 1,
    topologyTime: Timestamp({ t: 1672180651, i: 3 })
  }
]
---
active mongoses
[ { '6.0.3': 1 } ]
---
autosplit
{ 'Currently enabled': 'yes' }
---
balancer
{
  'Currently running': 'no',
  'Currently enabled': 'yes',
  'Failed balancer rounds in last 5 attempts': 0,
  'Migration Results for the last 24 hours': { '6': 'Success' }
}
---
databases
[
  {
    database: { _id: 'config', primary: 'config', partitioned: true },
    collections: {
      'config.system.sessions': {
        shardKey: { _id: 1 },
        unique: false,
        balancing: true,
        chunkMetadata: [ { shard: 'shard1Set', nChunks: 1024 } ],
        chunks: [
          'too many chunks to print, use verbose if you want to force print'
        ],
        tags: []
      }
    }
  },
  {
    database: {
      _id: 'ourBase',
      primary: 'shard1Set',
      partitioned: false,
      version: {
        uuid: new UUID("3125bfef-0d8d-42aa-b3ee-20c8456a2b2e"),
        timestamp: Timestamp({ t: 1672180771, i: 2 }),
        lastMod: 1
      }
    },
    collections: {
      'ourBase.col': {
        shardKey: { a: 1 },
        unique: false,
        balancing: true,
        chunkMetadata: [
          { shard: 'shard1Set', nChunks: 1 },
          { shard: 'shard2Set', nChunks: 1 },
          { shard: 'shard3Set', nChunks: 1 }
        ],
        chunks: [
          { min: { a: MinKey() }, max: { a: 'c' }, 'on shard': 'shard1Set', 'last modified': Timestamp({ t: 3, i: 1 }) },
          { min: { a: 'c' }, max: { a: 'e' }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 2, i: 0 }) },
          { min: { a: 'e' }, max: { a: MaxKey() }, 'on shard': 'shard3Set', 'last modified': Timestamp({ t: 3, i: 0 }) }
        ],
        tags: []
      },
      'ourBase.col_hash': {
        shardKey: { a: 'hashed' },
        unique: false,
        balancing: true,
        chunkMetadata: [
          { shard: 'shard1Set', nChunks: 2 },
          { shard: 'shard2Set', nChunks: 2 },
          { shard: 'shard3Set', nChunks: 2 }
        ],
        chunks: [
          { min: { a: MinKey() }, max: { a: Long("-6148914691236517204") }, 'on shard': 'shard1Set', 'last modified': Timestamp({ t: 1, i: 0 }) },
          { min: { a: Long("-6148914691236517204") }, max: { a: Long("-3074457345618258602") }, 'on shard': 'shard1Set', 'last modified': Timestamp({ t: 1, i: 1 }) },
          { min: { a: Long("-3074457345618258602") }, max: { a: Long("0") }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 1, i: 2 }) },
          { min: { a: Long("0") }, max: { a: Long("3074457345618258602") }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 1, i: 3 }) },
          { min: { a: Long("3074457345618258602") }, max: { a: Long("6148914691236517204") }, 'on shard': 'shard3Set', 'last modified': Timestamp({ t: 1, i: 4 }) },
          { min: { a: Long("6148914691236517204") }, max: { a: MaxKey() }, 'on shard': 'shard3Set', 'last modified': Timestamp({ t: 1, i: 5 }) }
        ],
        tags: []
      }
    }
  }
]
```

```bash
shard1Set [direct: primary] ourBase> rs.conf()
{
  _id: 'shard1Set',
  version: 4,
  term: 1,
  members: [
    {
      _id: 0,
      host: '127.0.0.1:27018',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 1,
      host: '127.0.0.1:27021',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 2,
      host: '127.0.0.1:27022',
      arbiterOnly: true,
      buildIndexes: true,
      hidden: false,
      priority: 0,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    }
  ],
  protocolVersion: Long("1"),
  writeConcernMajorityJournalDefault: true,
  settings: {
    chainingAllowed: true,
    heartbeatIntervalMillis: 2000,
    heartbeatTimeoutSecs: 10,
    electionTimeoutMillis: 10000,
    catchUpTimeoutMillis: -1,
    catchUpTakeoverDelayMillis: 30000,
    getLastErrorModes: {},
    getLastErrorDefaults: { w: 1, wtimeout: 0 },
    replicaSetId: ObjectId("63ab64f9e3b4a3e97f2dc005")
  }
}
```

```bash
shard1Set [direct: primary] ourBase> rs.status()
{
  set: 'shard1Set',
  date: ISODate("2022-12-28T15:00:40.205Z"),
  myState: 1,
  term: Long("1"),
  syncSourceHost: '',
  syncSourceId: -1,
  heartbeatIntervalMillis: Long("2000"),
  majorityVoteCount: 2,
  writeMajorityCount: 2,
  votingMembersCount: 3,
  writableVotingMembersCount: 2,
  optimes: {
    lastCommittedOpTime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
    lastCommittedWallTime: ISODate("2022-12-28T15:00:35.177Z"),
    readConcernMajorityOpTime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
    appliedOpTime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
    durableOpTime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
    lastAppliedWallTime: ISODate("2022-12-28T15:00:35.177Z"),
    lastDurableWallTime: ISODate("2022-12-28T15:00:35.177Z")
  },
  lastStableRecoveryTimestamp: Timestamp({ t: 1672239605, i: 1 }),
  electionCandidateMetrics: {
    lastElectionReason: 'electionTimeout',
    lastElectionDate: ISODate("2022-12-27T21:34:49.498Z"),
    electionTerm: Long("1"),
    lastCommittedOpTimeAtElection: { ts: Timestamp({ t: 1672176889, i: 1 }), t: Long("-1") },
    lastSeenOpTimeAtElection: { ts: Timestamp({ t: 1672176889, i: 1 }), t: Long("-1") },
    numVotesNeeded: 1,
    priorityAtElection: 1,
    electionTimeoutMillis: Long("10000"),
    newTermStartDate: ISODate("2022-12-27T21:34:49.534Z"),
    wMajorityWriteAvailabilityDate: ISODate("2022-12-27T21:34:49.556Z")
  },
  members: [
    {
      _id: 0,
      name: '127.0.0.1:27018',
      health: 1,
      state: 1,
      stateStr: 'PRIMARY',
      uptime: 64301,
      optime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
      optimeDate: ISODate("2022-12-28T15:00:35.000Z"),
      lastAppliedWallTime: ISODate("2022-12-28T15:00:35.177Z"),
      lastDurableWallTime: ISODate("2022-12-28T15:00:35.177Z"),
      syncSourceHost: '',
      syncSourceId: -1,
      infoMessage: '',
      electionTime: Timestamp({ t: 1672176889, i: 2 }),
      electionDate: ISODate("2022-12-27T21:34:49.000Z"),
      configVersion: 4,
      configTerm: 1,
      self: true,
      lastHeartbeatMessage: ''
    },
    {
      _id: 1,
      name: '127.0.0.1:27021',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 57138,
      optime: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
      optimeDurable: { ts: Timestamp({ t: 1672239635, i: 1 }), t: Long("1") },
      optimeDate: ISODate("2022-12-28T15:00:35.000Z"),
      optimeDurableDate: ISODate("2022-12-28T15:00:35.000Z"),
      lastAppliedWallTime: ISODate("2022-12-28T15:00:35.177Z"),
      lastDurableWallTime: ISODate("2022-12-28T15:00:35.177Z"),
      lastHeartbeat: ISODate("2022-12-28T15:00:38.533Z"),
      lastHeartbeatRecv: ISODate("2022-12-28T15:00:39.552Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27018',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 4,
      configTerm: 1
    },
    {
      _id: 2,
      name: '127.0.0.1:27022',
      health: 1,
      state: 7,
      stateStr: 'ARBITER',
      uptime: 55151,
      lastHeartbeat: ISODate("2022-12-28T15:00:39.730Z"),
      lastHeartbeatRecv: ISODate("2022-12-28T15:00:39.749Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '',
      syncSourceId: -1,
      infoMessage: '',
      configVersion: 4,
      configTerm: 1
    }
  ],
  ok: 1,
  lastCommittedOpTime: Timestamp({ t: 1672239635, i: 1 }),
  '$clusterTime': {
    clusterTime: Timestamp({ t: 1672239635, i: 1 }),
    signature: {
      hash: Binary(Buffer.from("0000000000000000000000000000000000000000", "hex"), 0),
      keyId: Long("0")
    }
  },
  operationTime: Timestamp({ t: 1672239635, i: 1 })
}
```

## project - logistic system

### Nodes setting

#### start servers
```cmd
mongod --configsvr --port 27017 --dbpath .\data_dbs\config --replSet confSet
mongod --shardsvr --port 27018 --dbpath .\data_dbs\db1 --replSet shard1Set
mongod --shardsvr --port 27019 --dbpath .\data_dbs\db2 --replSet shard2Set
mongod --port 27020 --dbpath .\data_dbs\db3 --replSet shard1Set
mongod --port 27021 --dbpath .\data_dbs\db4 --replSet shard1Set
mongod --port 27022 --dbpath .\data_dbs\db5 --replSet shard1Set
mongod --port 27023 --dbpath .\data_dbs\db6 --replSet shard2Set
mongod --port 27024 --dbpath .\data_dbs\db7 --replSet shard2Set
mongod --port 27025 --dbpath .\data_dbs\db8 --replSet shard2Set
mongos --configdb confSet/127.0.0.1:27017 --port 27016
start cmd /K mongosh --port 27017
start cmd /K mongosh --port 27018
start cmd /K mongosh --port 27019
```

**第二次**打开后，primary replicaSet 可能是会变的，同时，对于replica应添加命令 `--shardsvr`
```cmd
mongod --configsvr --port 27017 --dbpath .\data_dbs\config --replSet confSet
mongod --shardsvr --port 27018 --dbpath .\data_dbs\db1 --replSet shard1Set
mongod --shardsvr --port 27019 --dbpath .\data_dbs\db2 --replSet shard2Set
mongod --shardsvr --port 27020 --dbpath .\data_dbs\db3 --replSet shard1Set
mongod --shardsvr --port 27021 --dbpath .\data_dbs\db4 --replSet shard1Set
mongod --shardsvr --port 27022 --dbpath .\data_dbs\db5 --replSet shard1Set
mongod --shardsvr --port 27023 --dbpath .\data_dbs\db6 --replSet shard2Set
mongod --shardsvr --port 27024 --dbpath .\data_dbs\db7 --replSet shard2Set
mongod --shardsvr --port 27025 --dbpath .\data_dbs\db8 --replSet shard2Set
mongos --configdb confSet/127.0.0.1:27017 --port 27016
start cmd /K mongosh --port 27017
start cmd /K mongosh --port 27018
start cmd /K mongosh --port 27019
start cmd /K mongosh --port 27016
```

#### initiate configure server and shard server
```cmd
rs.initiate({_id:"confSet", configsvr: true, members: [{_id: 0, host: "127.0.0.1:27017"}]})
rs.initiate( { _id: "shard1Set", members: [ { _id: 0, host: "127.0.0.1:27018"}]})
rs.initiate( { _id: "shard2Set", members: [ { _id: 0, host: "127.0.0.1:27019"}]})
```

#### start router
```cmd
mongosh --port 27016
sh.addShard("shard1Set/127.0.0.1:27018")
sh.addShard("shard2Set/127.0.0.1:27019")
sh.enableSharding("logistic")
```

#### add replication nodes
##### shard1
```cmd
rs.add('127.0.0.1:27020')
rs.add('127.0.0.1:27021')
rs.add('127.0.0.1:27022')
cfg=rs.conf()
cfg.members[3].proprity=0
cfg.members[3].votes=0 
cfg.members[3].hidden=true
rs.reconfig(cfg)
```

##### shard2
```cmd
rs.add('127.0.0.1:27023')
rs.add('127.0.0.1:27024')
rs.add('127.0.0.1:27025')
cfg=rs.conf()
cfg.members[3].proprity=0
cfg.members[3].votes=0 
cfg.members[3].hidden=true
rs.reconfig(cfg)
```

### set range shard of one collection
1. in **mongos** process (i.e. port 27016)
  ```cmd
  use logistic
  sh.shardCollection("logistic.packages", {"from.city": 1})
  sh.splitAt("logistic.packages", {"from.city":"Gdansk"})
  sh.splitAt("logistic.packages", {"from.city":"Gdynia"})
  sh.splitAt("logistic.packages", {"from.city":"Sopot"})
  sh.splitAt("logistic.packages", {"from.city":"Warsaw"})
  ```

2. see which shard is primary shard
  ```
  sh.status()
  ```

3. move chunks
  ```
  sh.moveChunk("logistic.packages", {"from.city":"Sopot"},  'shard1Set')
  sh.moveChunk("logistic.packages", {"from.city":"Warsaw"},   'shard1Set')
  ```

4. Later can use it to check shard
  ```
  db.packages.find({},{_id:1,"from.city":1})
  ```

### Create documents
#### collection - packages
```bash
db.packages.insertMany([
  {
    "_id" : "package_0",
    "status" : "delivering",
    "from" : {
      "city": "Gdansk",
      "address" : "xxxx street",
      "name" : "DuGuYifei",
      "phone" : "606505111"
   },
   "delivery" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Jakub",
      "phone" : "606505222"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 1234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_0",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_1",
        "date" : ISODate("2022-06-21T23:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_2",
        "date" : ISODate("2022-06-22T07:00:00Z")
      },
      {
        "action" : "delivering",
        "operator" : "deliverer 6789",
        "date" : ISODate("2022-06-23T02:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_1",
    "status" : "finished",
    "from" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Jak",
      "phone" : "606505333"
   },
   "delivery" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Piot",
      "phone" : "606505444"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 2234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_0",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_1",
        "date" : ISODate("2022-06-21T23:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_2",
        "date" : ISODate("2022-06-22T07:00:00Z")
      },
      {
        "action" : "delivering",
        "operator" : "deliverer 6789",
        "date" : ISODate("2022-06-23T02:00:00Z")
      },
      {
        "action" : "in_express_locker",
        "operator" : "deliverer 6789",
        "date" : ISODate("2022-06-23T02:00:00Z")
      },
      {
        "action" : "finished",
        "date" : ISODate("2016-06-23T08:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_2",
    "status" : "shipping",
    "from" : {
      "city": "Gdansk",
      "address" : "xxxx street",
      "name" : "Jak",
      "phone" : "606505333"
   },
   "delivery" : {
      "city": "Sopot",
      "address" : "xxxx street",
      "name" : "Fei",
      "phone" : "606505666"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 2234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_0",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_1",
        "date" : ISODate("2022-06-21T23:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_3",
    "status" : "shipping",
    "from" : {
      "city": "Gdansk",
      "address" : "xxxx street",
      "name" : "Piot",
      "phone" : "606505444"
   },
   "delivery" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505223"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 2234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_4",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_5",
        "date" : ISODate("2022-06-21T23:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_4",
    "status" : "shipping",
    "from" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505223"
   },
   "delivery" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Tobi",
      "phone" : "606505425"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 2234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_5",
        "date" : ISODate("2022-06-21T17:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_5",
    "status" : "shipping",
    "from" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505223"
   },
   "delivery" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Tobi",
      "phone" : "606505425"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 5234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_5",
        "date" : ISODate("2022-06-21T17:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_6",
    "status" : "in_express_locker",
    "from" : {
      "city": "Sopot",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505223"
   },
   "delivery" : {
      "city": "Gdansk",
      "address" : "xxxx street",
      "name" : "Tobi",
      "phone" : "606505425"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 5234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_5",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "in_express_locker",
        "operator" : "deliverer 6789",
        "date" : ISODate("2022-06-22T02:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_7",
    "status" : "in_express_locker",
    "from" : {
      "city": "Sopot",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505223"
   },
   "delivery" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Tobi Lu",
      "phone" : "606505625"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 5234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_8",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "in_express_locker",
        "operator" : "deliverer 2789",
        "date" : ISODate("2022-06-22T02:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_8",
    "status" : "finished",
    "from" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Yifei",
      "phone" : "606505723"
   },
   "delivery" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Jak",
      "phone" : "606505825"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 5234",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_3",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "in_express_locker",
        "operator" : "deliverer 2789",
        "date" : ISODate("2022-06-22T02:00:00Z")
      },
      {
        "action" : "finished",
        "date" : ISODate("2022-06-23T02:00:00Z")
      }
   ]
  },
  {
    "_id" : "package_9",
    "status" : "shipping",
    "from" : {
      "city": "Gdynia",
      "address" : "xxxx street",
      "name" : "Yifei DuGu",
      "phone" : "606505923"
   },
   "delivery" : {
      "city": "Warsaw",
      "address" : "xxxx street",
      "name" : "Piot",
      "phone" : "606505855"
   },
   "details" : [
      {
        "action" : "reviced",
        "operator" : "deliverer 5934",
        "date" : ISODate("2022-06-21T01:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_6",
        "date" : ISODate("2022-06-21T17:00:00Z")
      },
      {
        "action" : "shipping",
        "station" : "station_9",
        "date" : ISODate("2022-06-22T17:00:00Z")
      }
   ]
  }
])
```

```sh
db.stations.insertMany([
    {
        _id: "station_0",
        station_name: "Moonstone",
        station_address: "Gdansk, Turkusowa 43",
        principal: "employee_4",
        packages_stored: ["package_2", "package_7"]
    },
    {
        _id: "station_1",
        station_name: "Emerald",
        station_address: "Olsztyn, Sowia 144",
        principal: "employee_0",
        packages_stored: []
    },
    {
        _id: "station_2",
        station_name: "Diamond",
        station_address: "Krakow, Podmiejska 70",
        principal: "employee_3",
        packages_stored: ["package_0"]
    },
    {
        _id: "station_3",
        station_name: "Aquamarine",
        station_address: "Poznan, Dobrochny 127",
        principal: "employee_7",
        packages_stored: []
    },
    {
        _id: "station_4",
        station_name: "Garnet",
        station_address: "Lodz, Admiralska 97",
        principal: "employee_9",
        packages_stored: ["package_8", "package_4"]
    },
    {
        _id: "station_5",
        station_name: "Malachite",
        station_address: "Pcim, Dworcowa 40",
        principal: "employee_8",
        packages_stored: ["package_9", "package_6"]
    },
    {
        _id: "station_6",
        station_name: "Citrine",
        station_address: "Warszawa, Gajdy 46",
        principal: "employee_2",
        packages_stored: []
    },
    {
        _id: "station_7",
        station_name: "Lapis Lazuli",
        station_address: "Bydgoszcz, Polczynska 47",
        principal: "employee_1",
        packages_stored: []
    },
    {
        _id: "station_8",
        station_name: "Onyx",
        station_address: "Wroclaw, Marianna 77",
        principal: "employee_5",
        packages_stored: []
    },
    {
        _id: "station_9",
        station_name: "Opal",
        station_address: "Szczecin, Warszawska 16",
        principal: "employee_6",
        packages_stored: ["package_1", "package_3", "package_5"]
    }
]);
```

```sh
db.cabinets.insertMany([
  {
  	"_id": "cabinet_0",
  	"city": "Warsaw",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_1",
  			"code": "254878",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 6789"
  		},
  		{
  			"package_id": "package_8",
  			"code": "824655",
  			"expiration_date": ISODate("2022-06-26T02:00:00Z"),
  			"operation_date": ISODate("2022-06-22T02:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		},
  		{
  			"package_id": "package_9",
  			"code": "798775",
  			"expiration_date": ISODate("2022-06-27T17:00:00Z"),
  			"operation_date": ISODate("2022-06-17T23:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		}
  	]
  },
  {
  	"_id": "cabinet_1",
  	"city": "Sopot",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_2",
  			"code": "846548",
  			"expiration_date": ISODate("2022-06-25T23:00:00Z"),
  			"operation_date": ISODate("2022-06-21T23:00:00Z"),
  			"delivery_operator": "deliverer 8635"
  		}
  	]
  },
  {
  	"_id": "cabinet_2",
  	"city": "Gdynia",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_3",
  			"code": "487421",
  			"expiration_date": ISODate("2022-06-26T23:00:00Z"),
  			"operation_date": ISODate("2022-06-22T23:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		},
  		{
  			"package_id": "package_4",
  			"code": "376323",
  			"expiration_date": ISODate("2022-06-26T17:00:00Z"),
  			"operation_date": ISODate("2022-06-22T17:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		},
  		{
  			"package_id": "package_7",
  			"code": "986542",
  			"expiration_date": ISODate("2022-06-26T02:00:00Z"),
  			"operation_date": ISODate("2022-06-22T02:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		},
  		{
  			"package_id": "package_3",
  			"code": "852456",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 2789"
  		}
  	]
  },
  {
  	"_id": "cabinet_3",
  	"city": "Gdansk",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_6",
  			"code": "387985",
  			"expiration_date": ISODate("2022-06-26T02:00:00Z"),
  			"operation_date": ISODate("2022-06-22T02:00:00Z"),
  			"delivery_operator": "deliverer 6789"
  		}
  	]
  },
  {
  	"_id": "cabinet_4",
  	"city": "Poznan",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_9",
  			"code": "467931",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 7470"
  		},
  		{
  			"package_id": "package_8",
  			"code": "813279",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 7470"
  		}
  	]
  },
  {
  	"_id": "cabinet_5",
  	"city": "Krakow",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_2",
  			"code": "513579",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 3263"
  		}
  	]
  },
  {
  	"_id": "cabinet_6",
  	"city": "Szczecin",
  	"address": "xxxx street",
  	"packages": []
  },
  {
  	"_id": "cabinet_7",
  	"city": "Wroclaw",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_4",
  			"code": "827193",
  			"expiration_date": ISODate("2022-06-27T02:00:00Z"),
  			"operation_date": ISODate("2022-06-23T02:00:00Z"),
  			"delivery_operator": "deliverer 6698"
  		}
  	]
  },
  {
  	"_id": "cabinet_8",
  	"city": "Lublin",
  	"address": "xxxx street",
  	"packages": [
  		{
  			"package_id": "package_1",
  			"code": "785096",
  			"expiration_date": ISODate("2022-06-25T02:00:00Z"),
  			"operation_date": ISODate("2022-06-21T02:00:00Z"),
  			"delivery_operator": "deliverer 6725"
  		},
  		{
  			"package_id": "package_2",
  			"code": "323545",
  			"expiration_date": ISODate("2022-06-25T02:00:00Z"),
  			"operation_date": ISODate("2022-06-21T02:00:00Z"),
  			"delivery_operator": "deliverer 6725"
  		}
  	]
  },
  {
  	"_id": "cabinet_9",
  	"city": "Bialystok",
  	"address": "xxxx street",
  	"packages": []
  }
])
```

### query:
1. Send the code of package to customers phone number
  ```bash
  db.cabinets.aggregate([
    {$unwind: "$packages"}, 
    {$lookup: {
        from:"packages", 
        localField: "packages.package_id", 
        foreignField: "_id", 
        as: "joined"
      } 
    }, 
    {$project: {"packages.code":1, "joined.delivery.phone":1}}
  ])
  ```
2. Transfer station "Moonstone" want to send the status of package to the user’s phone number
  ```bash
  db.stations.aggregate([
    {$match: {"station_name":"Moonstone"}}, 
    {$unwind:"$packages_stored"}, 
    {$lookup: {
        from:"packages", 
        localField: "packages_stored", 
        foreignField: "_id", 
        as: "joined"
      }
    }, 
    {$project: {"_id":0, "station_name":1, "packages_stored":1, "joined.status":1, "joined.delivery.phone":1}}
  ])
  ```
3. User want to call to ask where is their package, so we need get the newest status of packages by phone number of receiver xxx-xxx-xxx (606505444)
  ```bash
  db.packages.aggregate([
    {$match:{"from.phone":"606505444"}}, 
    {$project:{latest:{$arrayElemAt:["$details",-1]}}}
  ]);
  ```
4. Customer which is sender of packges_3 wants to cancel the delivery, then he calls customer service, the customer servicer will try to find responsible person of the transfer station or the deliverer (depend on the status of package, "shipping" or "in_express_locker")
  ```bash
  db.packages.aggregate([
    {$match: {_id: "package_3"}},
    {$lookup: {
              from: "stations",
              localField: "details.station",
              foreignField: "_id",
              as: "joined"
            }},
    {
      $project:{
        responsible_person:{
          $cond:{
            if: {$eq: ["$status", "in_express_locker"]},
            then: {$arrayElemAt:["$details.operator",-1]},
            else: {$arrayElemAt:["$joined.principal",-1]}
          }
        }
      }
    }
  ])

  db.packages.aggregate([
    {$match: {_id: "package_6"}},
    {$lookup: {
              from: "stations",
              localField: "details.station",
              foreignField: "_id",
              as: "joined"
            }},
    {
      $project:{
        responsible_person:{
          $cond:{
            if: {$eq: ["$status", "in_express_locker"]},
            then: {$arrayElemAt:["$details.operator",-1]},
            else: {$arrayElemAt:["$joined.principal",-1]}
          }
        }
      }
    }
  ])
  ```

```bash
shard1Set [direct: primary] test> rs.conf()
{
  _id: 'shard1Set',
  version: 8,
  term: 6,
  members: [
    {
      _id: 0,
      host: '127.0.0.1:27018',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 1,
      host: '127.0.0.1:27020',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 2,
      host: '127.0.0.1:27021',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 3,
      host: '127.0.0.1:27022',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: true,
      priority: 0,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 0
    }
  ],
  protocolVersion: Long("1"),
  writeConcernMajorityJournalDefault: true,
  settings: {
    chainingAllowed: true,
    heartbeatIntervalMillis: 2000,
    heartbeatTimeoutSecs: 10,
    electionTimeoutMillis: 10000,
    catchUpTimeoutMillis: -1,
    catchUpTakeoverDelayMillis: 30000,
    getLastErrorModes: {},
    getLastErrorDefaults: { w: 1, wtimeout: 0 },
    replicaSetId: ObjectId("63b8c337f136c93d2afb3f28")
  }
}
###########################################################################
shard1Set [direct: primary] test> rs.status()
{
  set: 'shard1Set',
  date: ISODate("2023-01-08T17:50:40.790Z"),
  myState: 1,
  term: Long("6"),
  syncSourceHost: '',
  syncSourceId: -1,
  heartbeatIntervalMillis: Long("2000"),
  majorityVoteCount: 2,
  writeMajorityCount: 2,
  votingMembersCount: 3,
  writableVotingMembersCount: 3,
  optimes: {
    lastCommittedOpTime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
    lastCommittedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
    readConcernMajorityOpTime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
    appliedOpTime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
    durableOpTime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
    lastAppliedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
    lastDurableWallTime: ISODate("2023-01-08T17:50:39.816Z")
  },
  lastStableRecoveryTimestamp: Timestamp({ t: 1673200219, i: 1 }),
  electionCandidateMetrics: {
    lastElectionReason: 'electionTimeout',
    lastElectionDate: ISODate("2023-01-08T13:32:36.975Z"),
    electionTerm: Long("6"),
    lastCommittedOpTimeAtElection: { ts: Timestamp({ t: 0, i: 0 }), t: Long("-1") },
    lastSeenOpTimeAtElection: { ts: Timestamp({ t: 1673184647, i: 2 }), t: Long("5") },
    numVotesNeeded: 2,
    priorityAtElection: 1,
    electionTimeoutMillis: Long("10000"),
    numCatchUpOps: Long("0"),
    newTermStartDate: ISODate("2023-01-08T13:32:38.506Z"),
    wMajorityWriteAvailabilityDate: ISODate("2023-01-08T13:32:38.533Z")
  },
  members: [
    {
      _id: 0,
      name: '127.0.0.1:27018',
      health: 1,
      state: 1,
      stateStr: 'PRIMARY',
      uptime: 15505,
      optime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:39.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      syncSourceHost: '',
      syncSourceId: -1,
      infoMessage: '',
      electionTime: Timestamp({ t: 1673184756, i: 1 }),
      electionDate: ISODate("2023-01-08T13:32:36.000Z"),
      configVersion: 8,
      configTerm: 6,
      self: true,
      lastHeartbeatMessage: ''
    },
    {
      _id: 1,
      name: '127.0.0.1:27020',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15486,
      optime: { ts: Timestamp({ t: 1673200229, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200229, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:29.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:29.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:39.238Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:39.792Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27018',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    },
    {
      _id: 2,
      name: '127.0.0.1:27021',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15483,
      optime: { ts: Timestamp({ t: 1673200229, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200229, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:29.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:29.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:39.239Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:39.346Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27018',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    },
    {
      _id: 3,
      name: '127.0.0.1:27022',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15479,
      optime: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200239, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:39.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:39.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:39.816Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:40.324Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:39.430Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27021',
      syncSourceId: 2,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    }
  ],
  ok: 1,
  lastCommittedOpTime: Timestamp({ t: 1673200239, i: 1 }),
  '$clusterTime': {
    clusterTime: Timestamp({ t: 1673200239, i: 2 }),
    signature: {
      hash: Binary(Buffer.from("0000000000000000000000000000000000000000", "hex"), 0),
      keyId: Long("0")
    }
  },
  operationTime: Timestamp({ t: 1673200239, i: 1 })
}
##################################################################
shard2Set [direct: primary] test> rs.conf()
{
  _id: 'shard2Set',
  version: 8,
  term: 6,
  members: [
    {
      _id: 0,
      host: '127.0.0.1:27019',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 1,
      host: '127.0.0.1:27023',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 2,
      host: '127.0.0.1:27024',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    },
    {
      _id: 3,
      host: '127.0.0.1:27025',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: true,
      priority: 0,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 0
    }
  ],
  protocolVersion: Long("1"),
  writeConcernMajorityJournalDefault: true,
  settings: {
    chainingAllowed: true,
    heartbeatIntervalMillis: 2000,
    heartbeatTimeoutSecs: 10,
    electionTimeoutMillis: 10000,
    catchUpTimeoutMillis: -1,
    catchUpTakeoverDelayMillis: 30000,
    getLastErrorModes: {},
    getLastErrorDefaults: { w: 1, wtimeout: 0 },
    replicaSetId: ObjectId("63b8c340db5bd34aa318d25d")
  }
}
###############################
shard2Set [direct: primary] test> rs.status()
{
  set: 'shard2Set',
  date: ISODate("2023-01-08T17:50:16.679Z"),
  myState: 1,
  term: Long("6"),
  syncSourceHost: '',
  syncSourceId: -1,
  heartbeatIntervalMillis: Long("2000"),
  majorityVoteCount: 2,
  writeMajorityCount: 2,
  votingMembersCount: 3,
  writableVotingMembersCount: 3,
  optimes: {
    lastCommittedOpTime: { ts: Timestamp({ t: 1673200216, i: 1 }), t: Long("6") },
    lastCommittedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
    readConcernMajorityOpTime: { ts: Timestamp({ t: 1673200216, i: 1 }), t: Long("6") },
    appliedOpTime: { ts: Timestamp({ t: 1673200216, i: 1 }), t: Long("6") },
    durableOpTime: { ts: Timestamp({ t: 1673200216, i: 1 }), t: Long("6") },
    lastAppliedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
    lastDurableWallTime: ISODate("2023-01-08T17:50:16.395Z")
  },
  lastStableRecoveryTimestamp: Timestamp({ t: 1673200156, i: 1 }),
  electionCandidateMetrics: {
    lastElectionReason: 'electionTimeout',
    lastElectionDate: ISODate("2023-01-08T13:32:52.800Z"),
    electionTerm: Long("6"),
    lastCommittedOpTimeAtElection: { ts: Timestamp({ t: 0, i: 0 }), t: Long("-1") },
    lastSeenOpTimeAtElection: { ts: Timestamp({ t: 1673184647, i: 1 }), t: Long("4") },
    numVotesNeeded: 2,
    priorityAtElection: 1,
    electionTimeoutMillis: Long("10000"),
    numCatchUpOps: Long("0"),
    newTermStartDate: ISODate("2023-01-08T13:32:55.014Z"),
    wMajorityWriteAvailabilityDate: ISODate("2023-01-08T13:32:55.856Z")
  },
  members: [
    {
      _id: 0,
      name: '127.0.0.1:27019',
      health: 1,
      state: 1,
      stateStr: 'PRIMARY',
      uptime: 15476,
      optime: { ts: Timestamp({ t: 1673200216, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:16.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      syncSourceHost: '',
      syncSourceId: -1,
      infoMessage: '',
      electionTime: Timestamp({ t: 1673184772, i: 2 }),
      electionDate: ISODate("2023-01-08T13:32:52.000Z"),
      configVersion: 8,
      configTerm: 6,
      self: true,
      lastHeartbeatMessage: ''
    },
    {
      _id: 1,
      name: '127.0.0.1:27023',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15447,
      optime: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:06.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:06.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:15.808Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:16.483Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27019',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    },
    {
      _id: 2,
      name: '127.0.0.1:27024',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15444,
      optime: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:06.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:06.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:15.782Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:16.548Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27019',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    },
    {
      _id: 3,
      name: '127.0.0.1:27025',
      health: 1,
      state: 2,
      stateStr: 'SECONDARY',
      uptime: 15441,
      optime: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDurable: { ts: Timestamp({ t: 1673200206, i: 1 }), t: Long("6") },
      optimeDate: ISODate("2023-01-08T17:50:06.000Z"),
      optimeDurableDate: ISODate("2023-01-08T17:50:06.000Z"),
      lastAppliedWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastDurableWallTime: ISODate("2023-01-08T17:50:16.395Z"),
      lastHeartbeat: ISODate("2023-01-08T17:50:15.809Z"),
      lastHeartbeatRecv: ISODate("2023-01-08T17:50:14.822Z"),
      pingMs: Long("0"),
      lastHeartbeatMessage: '',
      syncSourceHost: '127.0.0.1:27019',
      syncSourceId: 0,
      infoMessage: '',
      configVersion: 8,
      configTerm: 6
    }
  ],
  ok: 1,
  lastCommittedOpTime: Timestamp({ t: 1673200216, i: 1 }),
  '$clusterTime': {
    clusterTime: Timestamp({ t: 1673200216, i: 1 }),
    signature: {
      hash: Binary(Buffer.from("0000000000000000000000000000000000000000", "hex"), 0),
      keyId: Long("0")
    }
  },
  operationTime: Timestamp({ t: 1673200216, i: 1 })
}
####################################
[direct: mongos] logistic> sh.status()
shardingVersion
{
  _id: 1,
  minCompatibleVersion: 5,
  currentVersion: 6,
  clusterId: ObjectId("63b8c316dc5855d8a554d822")
}
---
shards
[
  {
    _id: 'shard1Set',
    host: 'shard1Set/127.0.0.1:27018,127.0.0.1:27020,127.0.0.1:27021',
    state: 1,
    topologyTime: Timestamp({ t: 1673053829, i: 3 })
  },
  {
    _id: 'shard2Set',
    host: 'shard2Set/127.0.0.1:27019,127.0.0.1:27023,127.0.0.1:27024',
    state: 1,
    topologyTime: Timestamp({ t: 1673053830, i: 3 })
  }
]
---
active mongoses
[ { '6.0.3': 1 } ]
---
autosplit
{ 'Currently enabled': 'yes' }
---
balancer
{
  'Currently running': 'no',
  'Currently enabled': 'yes',
  'Failed balancer rounds in last 5 attempts': 0,
  'Migration Results for the last 24 hours': 'No recent migrations'
}
---
databases
[
  {
    database: { _id: 'config', primary: 'config', partitioned: true },
    collections: {
      'config.system.sessions': {
        shardKey: { _id: 1 },
        unique: false,
        balancing: true,
        chunkMetadata: [ { shard: 'shard1Set', nChunks: 1024 } ],
        chunks: [
          'too many chunks to print, use verbose if you want to force print'
        ],
        tags: []
      }
    }
  },
  {
    database: {
      _id: 'logistic',
      primary: 'shard2Set',
      partitioned: false,
      version: {
        uuid: new UUID("cb426d2e-fda6-4a54-8978-b5244bd37fa4"),
        timestamp: Timestamp({ t: 1673053941, i: 1 }),
        lastMod: 1
      }
    },
    collections: {
      'logistic.packages': {
        shardKey: { 'from.city': 1 },
        unique: false,
        balancing: true,
        chunkMetadata: [
          { shard: 'shard1Set', nChunks: 2 },
          { shard: 'shard2Set', nChunks: 3 }
        ],
        chunks: [
          { min: { 'from.city': MinKey() }, max: { 'from.city': 'Gdansk' }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 3, i: 1 }) },
          { min: { 'from.city': 'Gdansk' }, max: { 'from.city': 'Gdynia' }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 1, i: 3 }) },
          { min: { 'from.city': 'Gdynia' }, max: { 'from.city': 'Sopot' }, 'on shard': 'shard2Set', 'last modified': Timestamp({ t: 1, i: 5 }) },
          { min: { 'from.city': 'Sopot' }, max: { 'from.city': 'Warsaw' }, 'on shard': 'shard1Set', 'last modified': Timestamp({ t: 2, i: 0 }) },
          { min: { 'from.city': 'Warsaw' }, max: { 'from.city': MaxKey() }, 'on shard': 'shard1Set', 'last modified': Timestamp({ t: 3, i: 0 }) }
        ],
        tags: []
      }
    }
  }
]
```