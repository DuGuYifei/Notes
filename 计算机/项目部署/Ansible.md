# Ansible

## 1. 目录结构

```
ansible/
├── inventories/
│   ├── production/
│   │   ├── hosts.ini
│   │   └── group_vars/
│   │       ├── all.yml
│   │       ├── backend.yml
│   │       └── database.yml
│   └── staging/
│       ├── hosts.ini
│       └── group_vars/
│           └── all.yml
│
├── roles/
│   ├── common/
│   │   ├── tasks/
│   │   │   └── main.yml
│   │   ├── handlers/
│   │   │   └── main.yml
│   │   ├── templates/
│   │   │   └── ntp.conf.j2
│   │   ├── files/
│   │   │   └── some-script.sh
│   │   ├── vars/
│   │   │   └── main.yml
│   │   ├── defaults/
│   │   │   └── main.yml
│   │   └── meta/
│   │       └── main.yml
│   └── app/
│       ├── tasks/
│       ├── templates/
│       └── ...
│
├── playbooks/
│   ├── site.yml
│   ├── deploy.yml
│   └── maintenance.yml
│
├── requirements.yml
└── ansible.cfg
```

## 2. 变量读取覆盖顺序

1. Role defaults（roles/*/defaults/main.yml）
2. Inventory group_vars/all
3. Inventory group_vars/<group>
4. Inventory host_vars/<host>
5. Inventory 文件(hosts.ini 或 hosts.yml)中定义的变量
6. vars_files（playbook 中引用）
7. Play vars（在 play 中写 vars）
8. Role vars（roles/*/vars/main.yml）
9. set_facts / register 生成变量
10. Extra vars（-e 参数，最高优先级）

## 3. vault 使用示例

### 创建加密文件

```bash
ansible-vault create secret.yml
```

### 编辑加密文件

```bash
ansible-vault edit secret.yml
```

### 使用加密文件运行 playbook

```bash
ansible-playbook playbook.yml --ask-vault-pass

ansible-playbook playbook.yml --vault-password-file ~/.vault_pass.txt

ansible-playbook playbook.yml --vault-password-file ~/.vault_pass1.txt --vault-password-file ~/.vault_pass2.txt
```

## 4. 安装collection或role

```bash
ansible-galaxy collection install community.general
ansible-galaxy role install geerlingguy.nginx
```

requirements.yml 示例：

```yaml
collections:
  - name: community.general
    version: ">=3.0.0"
roles:
  - name: geerlingguy.nginx
    version: ">=3.0.0"
```

## 5. 常用启动命令

```bash
ansible-playbook playbooks/site.yml \
  --inventory inventories/production/hosts.ini \
  --ask-pass \
  --become \
  --ask-become-pass \
  --vault-password-file ~/.vault_pass.txt \
  --extra-vars "env=production deploy_tag=v3.0.0 restart=yes" \
```
    