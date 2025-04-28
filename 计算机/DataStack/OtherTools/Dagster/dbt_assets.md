# dbt_assets

`assets.py`:

```python
from dagster import AssetExecutionContext
from dagster_dbt import dbt_assets, DbtCliResource
from pathlib import Path

# 定义 dbt 项目的路径
DBT_PROJECT_DIR = Path(__file__).resolve().parent.parent.parent / "dbt_project"
DBT_PROFILES_DIR = DBT_PROJECT_DIR  # 假设 profiles.yml 在 dbt_project 目录下

if not (DBT_PROJECT_DIR / "target" / "manifest.json").exists():
    raise FileNotFoundError("manifest.json not found, please run `dbt compile` first.")


@dbt_assets(manifest=DBT_PROJECT_DIR / "target" / "manifest.json")
def load_dbt_assets(context: AssetExecutionContext, dbt: DbtCliResource):
    yield from dbt.cli(["build"], context=context).stream()
```

`definitions.py`:

```python
from dagster import Definitions
from dagster_dbt import DbtCliResource
from .assets import load_dbt_assets
from pathlib import Path

# 定义 dbt 项目的路径
DBT_PROJECT_DIR = Path(__file__).resolve().parent.parent.parent / "dbt_project"
DBT_PROFILES_DIR = DBT_PROJECT_DIR

# 配置 DbtCliResource
dbt_resource = DbtCliResource(
    project_dir=str(DBT_PROJECT_DIR),
    profiles_dir=str(DBT_PROFILES_DIR),
)

# 注册 dbt 资产和资源
defs = Definitions(
    assets=[load_dbt_assets],
    resources={"dbt": dbt_resource},
)
```