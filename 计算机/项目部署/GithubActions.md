# Github Actions

- [一、GitHub Actions 是什么](#一github-actions-是什么)
- [二、GitHub Actions 的核心概念](#二github-actions-的核心概念)
    - [1. Workflow（工作流）](#1-workflow工作流)
    - [2. Event（触发事件）](#2-event触发事件)
    - [3. Job（任务）](#3-job任务)
    - [4. Step（步骤）](#4-step步骤)
    - [5. Action（动作）](#5-action动作)
- [三、GitHub Actions 的常用场景](#三github-actions-的常用场景)
    - [1. CI：自动化构建与测试](#1-ci自动化构建与测试)
    - [2. CD：自动部署](#2-cd自动部署)
    - [3. IaC 自动化](#3-iac-自动化)
    - [4. 自动管理 Repo](#4-自动管理-repo)
    - [5. 安全与扫描](#5-安全与扫描)
- [四、GitHub Actions 工作原理（内部机制）](#四github-actions-工作原理内部机制)
- [五、一个最基础的 Workflow 示例](#五一个最基础的-workflow-示例)
- [六、常用场景示例](#六常用场景示例)
  - [1. Node.js 项目 CI](#1-nodejs-项目-ci)
  - [2. Docker 构建并推送到 DockerHub](#2-docker-构建并推送到-dockerhub)
  - [3. 用 GitHub Actions 部署到 AWS（Lambda / ECS 等）](#3-用-github-actions-部署到-awslambda--ecs-等)
- [七、Secrets 管理](#七secrets-管理)
- [八、Runner 类型](#八runner-类型)
    - [1. GitHub-hosted Runner](#1-github-hosted-runner)
    - [2. Self-hosted Runner](#2-self-hosted-runner)
- [九、GitHub Actions 的最佳实践](#九github-actions-的最佳实践)



## 一、GitHub Actions 是什么

GitHub Actions 是 GitHub 内置的自动化工作流平台，可用于：

* 自动化构建（Build）
* 自动化测试（Test）
* 自动化部署（Deploy）
* 持续集成与持续交付（CI/CD）
* 基础设施自动化（如触发 Terraform）
* 定时任务（Cron）
* 自动回复 Issues / PR
* 代码质量检查、Lint、SAST 等

它允许你通过 YAML 文件定义工作流，并在 GitHub 托管的 runner 上执行任务。

---

## 二、GitHub Actions 的核心概念

#### 1. Workflow（工作流）

* 一个 YAML 文件定义的一组自动化步骤。
* 位于 `.github/workflows/*.yml`。

#### 2. Event（触发事件）

常见触发方式：

* `push`
* `pull_request`
* `workflow_dispatch`（手动执行）
* `schedule`（cron）
* `release`
* `issues`、`pull_request_target` 等 GitHub 事件

示例：

```yaml
on: push
```

---

#### 3. Job（任务）

* 一个 workflow 可以有多个 job。
* 默认并行运行，也可以用 `needs:` 定义依赖关系。

示例：

```yaml
jobs:
  build:
    runs-on: ubuntu-latest
```

---

#### 4. Step（步骤）

* 每个 job 由多个 step 组成。
* step 可以执行 shell 命令或使用 action。

示例：

```yaml
steps:
  - run: echo "Hello World"
```

---

#### 5. Action（动作）

* step 中的可复用功能模块。
* GitHub Marketplace 有大量 Action：

  * checkout
  * setup-node
  * docker login
  * aws-actions/configure-aws-credentials

示例：

```yaml
uses: actions/checkout@v4
```

---

## 三、GitHub Actions 的常用场景

#### 1. CI：自动化构建与测试

* Node.js 项目执行 `npm install && npm test`
* Java 项目执行 Maven / Gradle
* Python 执行 `pytest`

#### 2. CD：自动部署

* 部署到 AWS、Azure、GCP
* 部署到 Kubernetes
* 部署到 Vercel / Netlify
* 构建 Docker 镜像并推送到 Registry

#### 3. IaC 自动化

* 运行 `terraform plan` / `apply`
* 运行 Ansible playbook

#### 4. 自动管理 Repo

* 自动 label PR / Issue
* 自动关闭 inactive issue
* 自动添加 Reviewer

#### 5. 安全与扫描

* CodeQL 安全扫描
* Dependabot 自动更新依赖

---

## 四、GitHub Actions 工作原理（内部机制）

1. GitHub 监听事件（如 push）。
2. 匹配 `.github/workflows/*.yml` 中对应 workflow。
3. 调度到 runner（GitHub-hosted 或 self-hosted）。
4. 在 runner 中按照顺序执行步骤。
5. 输出日志、Artifacts、测试报告。
6. 最后返回执行状态（成功 / 失败）。

---

## 五、一个最基础的 Workflow 示例

在 `.github/workflows/hello.yml` 中：

```yaml
name: Hello CI

on: push

jobs:
  say_hello:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout source
        uses: actions/checkout@v4

      - name: Print message
        run: echo "Hello GitHub Actions"
```

---

## 六、常用场景示例

### 1. Node.js 项目 CI

```yaml
name: Node CI

on:
  push:
    branches: [ main ]
  pull_request:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-node@v4
        with:
          node-version: "18"

      - run: npm install
      - run: npm test
```

---

### 2. Docker 构建并推送到 DockerHub

```yaml
name: Build Docker

on: push

jobs:
  docker:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - name: Login to DockerHub
        uses: docker/login-action@v3
        with:
          username: ${{ secrets.DOCKERHUB_USER }}
          password: ${{ secrets.DOCKERHUB_TOKEN }}

      - name: Build and push
        uses: docker/build-push-action@v4
        with:
          push: true
          tags: myrepo/myimage:latest
```

---

### 3. 用 GitHub Actions 部署到 AWS（Lambda / ECS 等）

例如部署到 S3：

```yaml
name: Deploy S3

on:
  push:
    branches: [ main ]

jobs:
  deploy:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - uses: aws-actions/configure-aws-credentials@v4
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET }}
          aws-region: us-east-1

      - name: Sync to S3
        run: aws s3 sync ./dist s3://my-bucket/ --delete
```

---

## 七、Secrets 管理

GitHub Actions 支持加密变量：

* 仓库级 Secrets
* Organization 级 Secrets
* 环境级 Secrets

使用方式：

```yaml
${{ secrets.MY_SECRET }}
```

---

## 八、Runner 类型

#### 1. GitHub-hosted Runner

GitHub 提供的虚拟机：

* ubuntu-latest
* windows-latest
* macos-latest

优点：简单
缺点：速度受限，不可控

#### 2. Self-hosted Runner

自己搭机器当 runner：

* 部署在云上（EC2）
* 部署在 Kubernetes
* 公司内网服务器

优点：性能可控、适合大型构建
缺点：维护成本高

---

## 九、GitHub Actions 的最佳实践

1. 使用 workflow 分离 CI 和 CD
2. 使用缓存加速构建（actions/cache）
3. 尽量复用 Action，而不是写 shell 命令
4. 在 PR 中启用 `terraform plan` 等“只读”操作
5. 使用 matrix 批量测试不同版本（例如 Node.js 16/18/20）
6. 用 Environments 设置审批流程（如生产环境执行前需审核）

