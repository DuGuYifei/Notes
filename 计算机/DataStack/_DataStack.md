# Data Stack

1. [数据库](./数据库/_数据库.md)
2. [Big Data](./BigData/_BigData.md)
3. [Other Tools](./OtherTools/_OtherTools.md)
4. [DBSAndModernCPUArch](./DBSAndModernCPUArch/DBSAndModernCPUArch.md)


“Modern Data Stack”（现代数据栈）是指一组用于现代数据处理与分析的工具集合，通常部署在云端，强调模块化、可扩展性、实时处理和易于协作。下面是按类别列出的完整组件（截至2025年的主流架构）：

## MSD

### 现代数据栈（Modern Data Stack）概述

---

### 一、数据源（Data Sources）
- 业务数据库：PostgreSQL、MySQL、SQL Server、Oracle、MongoDB
- SaaS应用：Salesforce、Zendesk、Shopify、Google Analytics、Stripe、Hubspot、Facebook Ads 等
- 事件跟踪：Segment、Snowplow、Heap、Mixpanel

---

### 二、数据提取与加载（Data Ingestion / ELT Tools）
- Fivetran  
- Airbyte  
- Stitch  
- Meltano  
- Hevo  
- Matillion  
- Estuary  
- RudderStack（也包含事件收集）

---

### 三、数据仓库 / 数据湖（Data Warehouse / Lake / Lakehouse）
- Snowflake  
- BigQuery  
- Amazon Redshift  
- Azure Synapse  
- Databricks（Lakehouse）  
- ClickHouse  
- Apache Iceberg / Delta Lake / Hudi（数据湖格式）

---

### 四、数据建模与转换（Transformation / Modeling）
- dbt（Data Build Tool）  
- Dataform（已被 Google Cloud 收购）  
- Coalesce  
- Transform.io  
- SQLMesh  
- Mozart Data（ETL + 转换）

---

### 五、数据编排（Orchestration & Workflow Scheduling）
- Airflow  
- Dagster  
- Prefect  
- Mage  
- Kestra  
- Metaflow（Netflix 开源，偏机器学习）

---

### 六、数据质量与治理（Data Quality & Governance）
- Great Expectations  
- Monte Carlo  
- Soda  
- Datafold（数据差异检测）  
- Bigeye  
- Anomalo  
- Metaplane  
- Collibra（数据治理）  
- Alation（数据目录）

---

### 七、元数据管理与数据目录（Metadata / Catalog / Lineage）
- Amundsen（Lyft）  
- DataHub（LinkedIn 开源）  
- OpenMetadata  
- Marquez  
- Atlan  
- Castor  
- Secoda  
- Alation  
- Collibra

---

### 八、数据可视化与BI工具（BI / Visualization）
- Looker  
- Tableau  
- Power BI  
- Mode Analytics  
- Superset  
- Metabase  
- Sigma Computing  
- ThoughtSpot  
- Holistics  
- Lightdash（基于 dbt 的开源 BI）

---

### 九、实时数据处理与流处理（Real-time / Streaming）
- Apache Kafka  
- Apache Flink  
- Apache Spark Structured Streaming  
- Materialize  
- RisingWave  
- Redpanda  
- Confluent（Kafka 企业版）  
- Estuary（CDC + 流处理）

---

### 十、反向 ETL / 激活层（Reverse ETL / Operational Analytics）
- Census  
- Hightouch  
- Grouparoo（已停止维护）  
- RudderStack（部分支持）  
- Omnata  
- Polytomic  
- Shipyard

---

### 十一、权限管理与安全（Data Access Control & Security）
- Immuta  
- Okera（已被 Databricks 收购）  
- Privacera  
- Satori  
- Atlan（也有权限管理）

---

### 十二、人工智能与机器学习平台（ML/AI Layer）
- Feature Store：Feast、Tecton  
- ML Platform：Weights & Biases、Comet、MLflow、SageMaker、Vertex AI  
- 数据科学协作：Hex、Deepnote、JupyterHub、Observable

---
