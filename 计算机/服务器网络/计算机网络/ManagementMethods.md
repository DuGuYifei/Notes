# ManagementMethods

下表展示了网络设备的许多管理方法中的一些方法的优点和缺点。 一些解决方案（标有星号 *）在很大程度上取决于设备制造商的实施方法。

| Attribute                                | Local console (RS-232) | Remote console (telnet) | Remote console (SSH) | WWW (http) | WWW (https) | SNMP (v1) |
| ---------------------------------------- | ---------------------- | ----------------------- | -------------------- | ---------- | ----------- | --------- |
| Security                                 | very high              | low                     | high                 | low        | high        | low       |
| Device's resource use                    | low                    | low                     | medium               | high       | high        | medium    |
| Bandwidth use                            | low                    | low                     | low                  | high       | high        | low       |
| Difficulty of implementation in a device | low                    | low                     | high                 | medium     | high        | medium    |
| Dependence on device's configuration     | low                    | high                    | high                 | high       | high        | high      |
| Required prior knowledge of the device   | high                   | high                    | high                 | low        | low         | low       |
| Scalability of the method                | low                    | average                 | average              | low        | low         | high      |
| Ability to automate the method           | high*                  | high*                   | high*                | low        | very low    | high*     |
