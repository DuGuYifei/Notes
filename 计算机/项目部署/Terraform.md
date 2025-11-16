# Terraform

- [一、Terraform 常见用途](#一terraform-常见用途)
  - [1. 云资源自动化部署](#1-云资源自动化部署)
  - [2. 多云 / 混合云资源统一管理](#2-多云--混合云资源统一管理)
  - [3. CICD 自动化基础设施管理](#3-cicd-自动化基础设施管理)
  - [4. 作为 Kubernetes 资源管理工具（补充 Helm）](#4-作为-kubernetes-资源管理工具补充-helm)
  - [5. 创建 SaaS 服务资源](#5-创建-saas-服务资源)
- [二、Terraform 实际操作（从零到资源部署）](#二terraform-实际操作从零到资源部署)
  - [步骤 1：安装 Terraform](#步骤-1安装-terraform)
  - [步骤 2：创建项目目录](#步骤-2创建项目目录)
  - [步骤 3：编写 main.tf](#步骤-3编写-maintf)
  - [步骤 4：Terraform 初始化](#步骤-4terraform-初始化)
  - [步骤 5：预览变更（不执行）](#步骤-5预览变更不执行)
  - [步骤 6：正式部署](#步骤-6正式部署)
  - [步骤 7：销毁资源](#步骤-7销毁资源)
- [三、企业常用 Terraform 工作流（示例）](#三企业常用-terraform-工作流示例)
  - [CICD Pipeline 中常见步骤：](#cicd-pipeline-中常见步骤)
- [四、总结](#四总结)



Terraform 通常用于**基础设施即代码（Infrastructure as Code, IaC）**的管理与自动化。它能以声明式配置文件的方式统一管理云端与本地的数据中心资源，实现基础设施的可复制、可审计、可版本化。


## 一、Terraform 常见用途

### 1. 云资源自动化部署

最典型的用途，几乎所有团队使用 Terraform 的第一步都是：

* 创建云服务器（EC2 / ECS / CVM）
* 创建数据库（RDS / MySQL / PostgreSQL）
* 配置网络资源（VPC、子网、安全组）
* 创建负载均衡（ALB/NLB）
* 部署 Kubernetes 集群（EKS/AKS/GKE）

适用云：AWS、Azure、GCP、阿里云、腾讯云、华为云等。

---

### 2. 多云 / 混合云资源统一管理

Terraform 的 Provider 体系允许同时管理多个基础设施：

* AWS + VMware
* GCP + 阿里云
* 本地 IDC + 云资源

DevOps 团队常用它来构建统一的 IaC 管理层。

---

### 3. CICD 自动化基础设施管理

常用于：

* 在 GitLab CI / GitHub Actions 中自动执行 `terraform plan` 和 `terraform apply`
* 代码审核（MR/PR）触发基础设施更新

实现基础设施版本化管理。

---

### 4. 作为 Kubernetes 资源管理工具（补充 Helm）

虽然 Kubernetes 主要用 Helm/Kustomize 管理，Terraform 也用于：

* 创建 Kubernetes 集群（EKS/AKS/GKE）
* 创建并管理集群外部资源（数据库、负载均衡）
* 有时用于 CRD / Operator 管理（但不推荐替代 Helm）

---

### 5. 创建 SaaS 服务资源

Terraform 也能管理：

* GitHub 仓库、团队、权限
* Datadog dashboard
* Cloudflare DNS 记录
* Okta 身份管理资源

非常适合平台工程（Platform Engineering）团队。

---

## 二、Terraform 实际操作（从零到资源部署）

下面展示一个**完整的最小可运行示例**，在 AWS 上创建一个 EC2 实例。

### 步骤 1：安装 Terraform

```
brew install terraform     # macOS
choco install terraform    # Windows
sudo apt install terraform # Ubuntu（前提是添加 Hashicorp 源）
```

---

### 步骤 2：创建项目目录

```
mkdir tf-demo
cd tf-demo
```

---

### 步骤 3：编写 main.tf

```hcl
terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "example" {
  ami           = "ami-0c94855ba95c71c99"
  instance_type = "t2.micro"

  tags = {
    Name = "terraform-demo"
  }
}
```

---

### 步骤 4：Terraform 初始化

```
terraform init
```

---

### 步骤 5：预览变更（不执行）

```
terraform plan
```

---

### 步骤 6：正式部署

```
terraform apply
```

输入 `yes` 后，Terraform 会开始创建资源。

---

### 步骤 7：销毁资源

```
terraform destroy
```

---

## 三、企业常用 Terraform 工作流（示例）

### CICD Pipeline 中常见步骤：

1. `terraform fmt` → 格式化
2. `terraform validate` → 静态检查
3. `terraform plan -out planfile`
4. PR 合并后自动执行 `terraform apply planfile`
5. 使用 remote backend（如 S3 + DynamoDB 或 Terraform Cloud）存储状态文件

---

## 四、总结

Terraform 的主要价值在于：

* 基础设施声明式管理
* 自动化部署与更新
* 可版本化、可审计、可追踪
* 多云统一管理
