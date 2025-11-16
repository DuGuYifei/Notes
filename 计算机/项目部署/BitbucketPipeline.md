# Bitbucket Pipeline

## 一、简介

[Bitbucket Pipeline](https://bitbucket.org/product/features/pipelines) 是 Atlassian 提供的持续集成和持续交付（CI/CD）服务，允许开发团队在代码库中直接定义和运行自动化构建、测试和部署流程。通过 Bitbucket Pipeline，团队可以实现代码的自动化构建和部署，提高开发效率和代码质量。

## 二、核心概念

### 1. Pipeline（流水线）
* 一个 YAML 文件定义的一组自动化步骤。
* 位于代码库的根目录下，文件名为 `bitbucket-pipelines.yml`。

### 2. Step（步骤）
* Pipeline 中的基本执行单元。
* 每个 step 可以包含多个命令，按顺序执行。
* 其他还有 `steps`、`stage`、`parallel` 等概念，用于组织和管理步骤。

### 3. Service（服务）
* 用于在 step 中运行的辅助容器，如数据库等。
* 可以在 step 中定义需要的服务。

### 4. Trigger（触发器）
* 定义何时触发 Pipeline 的执行。
* 常见触发方式包括 `push`、`pull request`、`manual` 等。

### 5. define

## 三、示例配置

```yaml
options:
  Global options page
clone:
  Git clone behavior page
definitions:
  Cache and service container definitions page
image:
  Docker image options page
pipeline:
  Pipeline start options page
    parallel:
      Parallel step options page
    stage:
      Stage options page
    step:
      Step options page
```

```yaml
# Required Bitbucket Pipeline Variables (sanitized):
# - VAULT_ALL_PASSWORD
# - VAULT_PASSWORD
# - LOG_SERVICE_USERNAME
# - LOG_SERVICE_PASSWORD
# - REGISTRY_USERNAME
# - REGISTRY_PASSWORD
# - REGISTRY_URL
# - SSH_DEPLOY_KEY

definitions:
  images:
    jdk25: &jdk25-image
      name: placeholder.registry.com/ci-images/eclipse-temurin:25-jdk-base
      username: $REGISTRY_USERNAME
      password: $REGISTRY_PASSWORD

  steps:
    - step: &build-application
        name: Build & Push
        image: *jdk25-image
        size: 2x
        services:
          - docker
        script:
          - echo "This anchor must be used with script override."
          - exit 1
        artifacts:
          - tags/**
        caches:
          - docker
          - gradle
          - node

    - parallel: &build-applications
        steps:
          - step:
              <<: *build-application
              name: Build & Push service-A
              script:
                - ci/scripts/build.sh service-A
              output-variables:
                - SERVICE_A_IMAGE_TAG

          - step:
              <<: *build-application
              name: Build & Push service-B
              script:
                - ci/scripts/build.sh service-B
              output-variables:
                - SERVICE_B_IMAGE_TAG

    - step: &deploy-applications
        name: Deploy applications
        runs-on:
          - self.hosted
          - linux.shell
        script:
          - ci/scripts/deploy.sh
        downloads:
          - tags/**

    - step: &run-api-tests-all
        name: Run API Tests
        image: *jdk25-image
        size: 2x
        script:
          - cd api-tests
          - |
            ./gradlew clean test \
            --tests '*ApiTest' \
            -DtestServiceAHostname="https://${SERVICE_A_HOSTNAME}" \
            -DtestServiceBHostname="https://${SERVICE_B_HOSTNAME}"
        after-script:
          - echo "API tests completed."

pipelines:
  custom:
    Test Deployment:
      - variables:
        - name: DEPLOYMENT_NAMESPACE

      - step:
          name: Validate namespace
          runs-on:
            - self.hosted
            - linux.shell
          script:
            - |
              if [ -z "$DEPLOYMENT_NAMESPACE" ]; then
                echo "DEPLOYMENT_NAMESPACE is not set."
                exit 1
              fi

      - parallel: *build-applications

      - stage:
          name: Test Deployment
          deployment: Test
          steps:
            - step:
                name: Setup deployment environment variables
                runs-on:
                  - self.hosted
                  - linux.shell
                script:
                  - export BASE_DOMAIN=test.placeholder-domain.com
                  - export ENVIRONMENT=internal
                  - echo "ENVIRONMENT=$ENVIRONMENT" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_A_HOSTNAME=service-A-${DEPLOYMENT_NAMESPACE}.${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_B_HOSTNAME=service-B-${DEPLOYMENT_NAMESPACE}.${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "BASE_DOMAIN=$BASE_DOMAIN" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                output-variables:
                  - SERVICE_A_HOSTNAME
                  - SERVICE_B_HOSTNAME
                  - ENVIRONMENT
                  - BASE_DOMAIN

            - step:
                <<: *deploy-applications

      - step: *run-api-tests-all


    Stage & Production Deployment:
      - parallel: *build-applications

      - stage:
          name: Stage Deployment
          deployment: Stage
          steps:
            - step:
                name: Setup environment variables
                runs-on:
                  - self.hosted
                  - linux.shell
                script:
                  - export BASE_DOMAIN=stage.placeholder-domain.com
                  - export DEPLOYMENT_NAMESPACE=stage
                  - export ENVIRONMENT=internal
                  - echo "ENVIRONMENT=${ENVIRONMENT}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_A_HOSTNAME=${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_B_HOSTNAME=service-b.${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "BASE_DOMAIN=${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                output-variables:
                  - SERVICE_A_HOSTNAME
                  - SERVICE_B_HOSTNAME
                  - ENVIRONMENT
                  - BASE_DOMAIN

            - step:
                <<: *deploy-applications

      - step: *run-api-tests-all

      - stage:
          name: Production Deployment
          deployment: Production
          trigger: manual
          steps:
            - step:
                name: Setup production environment variables
                runs-on:
                  - self.hosted
                  - linux.shell
                script:
                  - export BASE_DOMAIN=prod.placeholder-domain.com
                  - export DEPLOYMENT_NAMESPACE=prod
                  - export ENVIRONMENT=production
                  - echo "ENVIRONMENT=${ENVIRONMENT}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_A_HOSTNAME=${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "SERVICE_B_HOSTNAME=service-b.${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                  - echo "BASE_DOMAIN=${BASE_DOMAIN}" >> $BITBUCKET_PIPELINES_VARIABLES_PATH
                output-variables:
                  - SERVICE_A_HOSTNAME
                  - SERVICE_B_HOSTNAME
                  - ENVIRONMENT
                  - BASE_DOMAIN

            - step:
                <<: *deploy-applications

      - step: *run-api-tests-all
```


## 四、bitbucket runners

有shell和docker两种类型，shell类型可以直接在宿主机上执行脚本，docker类型可以指定docker镜像在容器中执行脚本。

还有bitbucket cloud自己的runner。

bitbucket pipeline可以通过label来选择使用哪种runner。
