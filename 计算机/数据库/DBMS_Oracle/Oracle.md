**Pytania z enauczania**

1. **What is the difference between the Oracle database, Oracle instance and Oracle server?**

**Oracle instance** is a set of background processes and memory structures that enable database management.

**Oracle database** is a set of physical structures that store user data and other database data

**Server Oracle** includes: 

-  Oracle instance,
- Oracle database (now: container DB, pluggable DBs, but you are always connected to a single one)
- Additional files
- Dedicated server processes and dispatcher services
-  Listener process(es)

**Ładna odp:**

**Oracle instance** is a set of background processes and memory structures that enable database management. **Oracle database** is a set of physical structures that store user data and other database data. **Oracle server**, however, includes all: Oracle instance, Oracle database, some additional files, dedicated server processes, dispatcher services and listener process(es).

2. **What is the difference between dedicated and shared server modes?**

Oracle Database creates server processes to handle the requests of user processes connected to an instance. A server process can be either of the following:

- A **dedicated server process**, which services only one user process
    - For each connection a separate server process is created and PGA area is allocated
    - Resource-consuming for multiple users
- A **shared server process**, which can service multiple user processes
    - Listener passes connection request to a dispatcher and the dispatcher passes the request to the least loaded server process
    - Server processes load balancing (by expeditors)
    - Expeditor processes load balancing (by listener process)

**Ładna odp:**

**A dedicated server** process services only one user process. For each connection a separate server process is created and PGA area is allocated. It is very resource-consuming when it is for multiple users.

**A shared server process** can service multiple users at the same time. User makes a connection request which is then passed by the listener to a dispatcher and the dispatcher passes the request to the least loaded server process. 

3. **What are the processes of an Oracle instance and what they do?** 

**PMON** – **P**rocess **Mon**itor Process - **monitors the other background processes** and **performs process recovery** when a server or dispatcher process terminates abnormally; **cleans up the database buffer cache and frees resources** (resets the status of the active transaction table, releases locks, removes the process from active processes).

**SMON** – **S**ystem **Mon**itor process - **controls database consistency**, **initiates and performs instance recovery**, recovers terminated transaction, cleans up unused temporary segments

**DBWn** – **D**ata**b**ase **W**riter process - **writes the contents of database buffers to data files** – spontaneously or at a checkpoint

**LGWR** – **L**o**g** **wr**iter process - **writes the contents of redo log buffer to redo log files** (in order to rollback the transaction if needed); writes at commit; when redo log file is full, initiates a checkpoint

**CKPT** – **C**hec**kp**oin**t** process – **updates the control file and data file headers with checkpoint information** and **signals DBWn to write** blocks to disk

**MMON** – **M**anageability **Mon**itor process - **performs many tasks related to the Automatic Workload Repository (AWR)**; writes when a metric violates its threshold value, takes snapshots, captures statistics value for recently modified SQL objects.

**MMNL** –**M**anageability **M**o**n**itor **L**ite process - **writes statistics from the Active Session History** (ASH) buffer in the SGA to disk

**RECO** - **Rec**overer process - automatically **resolves failures in distributed transactions**

**ARCn** - **Arc**hiver process(es) - **copy online redo log files to offline storage after a redo log switch occurs**; collect transaction redo data and transmit it to standby database destinations; **ARCn processes exist only when the database is in ARCHIVELOG mode**

4. **What are the buffers of an Oracle instance and what they store?**

**Buffer Cache** – stores copies of data blocks read from data files; caches a currently or recently used data blocks (LRU); all users concurrently connected to a database instance share access to the buffer cache;

**Redo Log Buffer** – circular buffer that stores redo entries describing changes made to the database; redo record is a data structure that contains the information necessary to reconstruct, or redo, changes made to the database by DML or DDL operations;

**Ładna odp:**

There are 2 buffers in Oracle instance: Buffer Cache and Redo Log Buffer. **Buffer Cache** stores **copies of data blocks read from data files** and caches currently or recently used data blocks. All users connected to a database at the same time share access to the Buffer Cache. **Redo Log Buffer** is a **circular buffer that stores redo entries** describing changes made to the database.

NIE WIEM CZY SHARED POOL, LARGE POOL I JAVA POOL TEZ POWINNY BYC? 

**Shared pool** - caches various types of program data

– Library Cache – stores execution plan and executable SQL and PL/SQL code; used to shorten query compilation time; soft parse – reuses the code from the cache; hard parse – requires more processing (time!);

– Data Dictionary Cache – holds information about database objects; data dictionary is a collection of database tables and views containing reference information about the database, its structures, and its users;

– SQL Query Result Cache - stores the results of queries and query fragments (not data blocks)

– Pl/SQL Function Result Cache - stores the results PL/SQL functions

**Large Pool** – optional memory area intended for memory allocations that are larger than is  appropriate for the shared pool eg. while archiving

**Java Pool** – stores all session-specific Java code and data within the JVM

5. **What is the difference between PGA and SGA?**

**System global area (SGA)** - The SGA is a group of shared memory structures, known as _SGA components_, that contain data and control information for one Oracle Database instance. All server and background processes share the SGA. It is also known as the “Shared Global Area”. The SGA consists of the following components:

●       Database buffer cache

●       Redo log buffer

●       Shared pool

●       Java pool

●       Large pool (optional)

●       Streams pool

**Program global area (PGA)** - A PGA is a non-shared memory region that contains data and control information exclusively for use by an Oracle process. Oracle Database creates the PGA when an Oracle process starts. One PGA exists for each [**server process**](https://docs.oracle.com/database/121/CNCPT/glossary.htm#GUID-E660AC1C-B704-4DC1-A35A-DB49EFB34F4A) and background process. PGA contains:

●       Sort area – size depending on SORT_AREA_SIZE parameter

●       Session information and cursors’ states

**Ładna odp.**

**System Global Area,** also known as Shared Global Area, is a **group of shared memory structures** that contain data and control information for one Oracle Database instance.  All server and background processes share the SGA. The difference is that the **Program Global Area** is a **non-shared memory region** that contains data and control information exclusively for use by an Oracle process. One PGA exists for each server process and background process. 

6. **What is an ARCHIVELOG/NOARCHIVELOG mode of Oracle?**

ARCHIVELOG 

- literally: archiving a log before overwriting it
- Redo Log File is a circular storage – once it is full, it is written from the beginning and the information is overwritten (lost)
- in ARCHIVELOG mode - before overwriting - a copy of redo log file is created as an archive
- production databases must work in this mode

NOARCHIVELOG

- the opposite – the log is not archived and the redo data is overwritten (lost)
- might be used for non-production databases and is sometimes used for data warehouses

**Ładna odp:**

ARCHIVELOG  mode is a mode when a log is being archived before overwriting it. Redo Log File is a circular storage, which once it is full, it is written from the beginning and the information is overwritten (in result lost). In ARCHIVELOG before overwriting, a copy of this file is created as an archive. All production databases must work in this mode.

NOARCHIVELOG mode is the exact oposite. The log is not being archived and the redo data is overwitten/lost. It might be used for non-production databases and is sometimes used for data warehouses.

7.  **What are the files of an Oracle database and instance/server?**

**Oracle database files:**

– **Datafiles** – contain the **actual data of multiple user databases**, data dictionary, users, rights, etc.

– **Control files** – contain **status information** of the Oracle Database

– **Redo Log Files** – contain **redo records** (data structure that contains the **information necessary to reconstruct, or redo, changes** made to the database by DML or DDL operations)

**Other files:**

– **Password file** – DBA only password file (orapwd command to change)

– **Parameter** file – **instance initialization parameters** file – binary (SPFILE) and text (PFILE)

– **Archives of Redo Log** – created when redo log files are full (and only if a database is in ARCHIVELOG mode)

8. **How processes, buffers, and files are used in processing queries, DMLs and COMMIT commands?**

**SQL – SELECT query processing**

1. Parse - analysis

- Looking in previous queries in shared pool (library cache)
- Query syntax control, 
- Objects naming control (using data dictionary from Data dictionary cache),
- Blocking objects used in the parse phase
- Access rights control (using data dictionary from Data dictionary cache)
- Creating a query execution plan (action tree)
- Writing down a query and execution plan in Library cache

2. Execute

- Identification of the required records and its location
- Looking for the records in Buffer cache (LRU-least recently used)
- Reading records from datafiles to Buffer cache
- Cursor opening
- Fetch
- Sort

3. Send – from the cursor to the user app (client process)

**DML query execution**

1. Parse – as in SELECT queries
2. Execution

- Identification of the required records and its location
- Looking for the records in Buffer cache (LRU-least recently used)
- Reading records from datafiles to Buffer cache and additionally to Redo Log Buffer
- Blocking records used in the execution phase
- Modification of the data in Buffer cache (new values)
- Modification of the data status in Redo Log Buffer (old data for rollback)
- „Dirty” block – data in buffer are different from data in physical files

**COMMIT query execution**

1. Adding an entry with an SCN number in Redo Log Buffer
2.  LGWR process writes down the Redo Log Buffer to Redo Log Files
3. User/app is informed about commit
4. The actual commit entry is written down

9. **What is the profile mechanism used for and how?**

Profiles is a set of parameters that apply to a user. A profile is a **named set of resource limits and password parameters that restrict database usage and instance resources for a user**.  Profile **controls Authorisation policy and  Resource policy**.  If no profile is specified, then the user is assigned a default profile. Each user can have only one profile, and creating a new one supersedes any earlier one. A profile can be created, assigned to users, altered, and dropped at any time (using CREATE USER or ALTER USER) by any authorized database user. Profiles can be assigned only to users and not to roles or other profiles.

//z prezki 

• Initialisation parameter RESOURCE_LIMIT decides whether resource policies are enforced

– Set to „true” by default

• Database Resource Manager is a suggested way of managing resource policies

• Each user has a profile; if profile is not specified, default is used //

CREATE PROFILE profile_name LIMIT parameter list; 

ALTER PROFILE profile_name LIMIT parameter list; 

DROP PROFILE profile_name [CASCADE] ;

10. **What is the quota mechanism used for and how (including the effects of setting a lower quota)?**

A quota is the **amount of space allocated to a user in a tablespace**. It **designates the size to which user’s data can grow**. Reducing (or setting) the quota will not force removal of user data, it will not be allowed to grow.  0 – prohibition from creating objects in a given tablespace (default value); UNLIMITED – no limits on user’s objects in the given tablespace. System privilege UNLIMITED TABLESPACE overrides quota and allows for creating objects of any size in every tablespace

11. **What are the roles used for and how, what are their limitations?**

**Roles are named groups of related system and object privileges**. Roles reduce administrative work by:

- Collecting privileges of an user class with similar security needs in one place, and/or
- Collecting privileges required to run a given application in one place

Roles are not contained in schemas, therefore:

- They require names unique throughout the whole database and different than any user name

- Removing user that created a role does not remove the role from the database

Roles have limited facilities for application developers, because object privileges must be granted directly to work in PL/SQL scripts. 

Roles are created using statement: CREATE ROLE role1; Requires CREATE ROLE system privilege Roles are deleted using statement: DROP ROLE role1;

**Ładna odp:**

Roles are **named groups of related system and object privileges**. Roles reduce administrative work by collecting privileges of an user class with similar security needs and privileges required to run a given application in one place. Roles are not contained in the schemas, therefore: 

- They require names unique throughout the whole database and different than any user name
- Removing user that created a role does not remove the role from the database

Roles have limited facilities for application developers, because object privileges must be granted directly to work in PL/SQL scripts. To create a role, one has to have granted CREATE ROLE privilege.

12. **Explain the difference between system privileges and object privileges**

Privileges are divided into system and object privileges.  A system privilege is the right to perform an action or to perform actions on schema objects.  An object privilege grants permission to perform a particular action on a specific schema object. 

The difference between system and object privileges is that system privileges are used for server and database privileges. But object privileges are used to grant privileges on database objects like tables, stored procedures, indexes, etc. 

13. **Explain the cascading effects of revoking a privilege and in which cases these effects may occur (revoking system privileges, object privileges, and roles)**

Cascading effects are e.g.  **propagation of privilege revocation** for privileges granted WITH GRANT OPTION, revoking of privileges from named PL/SQL blocks created by the affected user. Revoking of REFERENCES privilege requires foreign key constraints to the affected object to be dropped. When revoking object privileges cascading effects can occur. No cascading effects occur when revoking system privileges or roles. Cascading effects can be observed when revoking a system privilege related to a DML operation.

Cascading effects:

- Propagation of privilege revocation for privileges granted WITH GRANT OPTION
- Revoking of the privileges from named PL/SQL blocks created by the affected user
- Revoking of REFERENCES privilege requires foreign key constraints to the affected object be dropped. 

14. **Explain what the audit mechanism is and what it is used for**

Auditing is the **monitoring and recording of** selected user database **actions**. Audit is done to: 

- Enable accountability for actions, 
- Deter reckless actions, 
- Monitor suspicious behavior, 
- Detect security settings problems, 
- Collect database activity data.

15. **Name layers of storage structures in Oracle and list structures belonging to the layers**

- User/Logic Layer
    - schema
    - table, index, view…
- Internal/Logic Layer
    - database
    - tablespace
    - segment
    - extent
    - DB block
- Physical Layer
    - datafile
    - disk block

16.  **Explain what is: schema, tablespace, segment, extent, DB block. Explain relations between those structures.**

Schema - set/container of related tables, indexes, views and other structures distinguishable for a user

Tablespace - logical storage unit, part of a database that is managed independently of the others – could be made read-only or off-line/on-line. Manages physical datafiles (one or many), single datafile is assigned to ONE tablespace.

Segment - Internal structure representing exactly one user schema object

Extent - Memory chunk allocated for a single segment, Continuous set of DB blocks

DB block - smallest unit of data used by a database, unit of read/write in datafiles in Oracle

Schemas are stored in tablespace, Tablespaces are divided into logical units of storage called segments. Segments are composed of extents and extents are composed of DB blocks. All elements created by the user in a schema are allocated in the form of segments in the tablespace. Particular segment is in 1 tablespace but a schema might not be (segments of the schema can be allocated in different tablespaces).

17.  **Name and describe files in Oracle database and in Oracle instance.**

Oracle database files:

– Datafiles – contain the actual data of multiple user databases, data dictionary, users, rights, etc.

– Control files – contain status information of the Oracle Database

– Redo Log Files – contain redo records (data structure that contains the information necessary to reconstruct, or redo, changes made to the database by DML or DDL operations)

Other files:

– Password file – DBA only password file (orapwd command to change)

– Parameter file – instance initialization parameters file – binary (SPFILE) and text (PFILE)

– Archives of Redo Log – created when redo log files are full (and only if a database is in ARCHIVELOG mode)

– Backup files 

– Logs – systems, errors, instance monitoring reports

18. **How are the extents allocated? On what it depends?**

**Extent** is always allocated **in a single datafile** (segment data might be stored in multiple datafiles within a single tablespace). When a tablespace has multiple datafiles, extensts are usually allocated alternately in all the files.  Extents are allocated and deallocated dynamically when a segment is created, updated or deleted.

Oracle uses different algorithms to allocate extents, d**epending on whether they are locally managed or dictionary managed**. With l**ocally managed tablespaces**, Oracle **looks for free space to allocate to a new extent** by first determining a candidate datafile in the tablespace and then searching the datafile's bitmap for the required number of adjacent free blocks. If that datafile does not have enough adjacent free space, then Oracle looks in another datafile.

19.  **Describe the DB block and parameters that manage how it is used.**

DB blocks consist of physical blocks. DB block is a unit of read/write in datafiles in Oracle.  The header contains general block information, such as the block address and the type of segment (for example, data or index). Table Directory contains information about the table having rows in this block. Row Directory contains information about the actual rows in the block (including addresses for each row piece in the row data area).Number of concurrent transations on a block: 

-  INITRANS – initial number of transaction slots (default 1) 
- MAXTRANS – max number of transaction slots (default 255) 

DB block fill management 

- PCTFREE – percentage of space reserved for existing rows extensions (if free space in a block is less, no new rows are inserted) – default 10% 
- PCTUSED – minimal use of a block that is to be maintained by Oracle (as data are removed from a block it will remain tagged as „full” until the use is less than this parameter) – default 40%

20. **What should be the difference in storage structures for OLAP and OLTP database? Why?**

OLAP: non-frequent reads and writes of large data sets ->  large DB blocks (biggest possible - improve reading performance)

OLTP: multiple reads and writes of small data records ->  small DB blocks (adjusted to transaction size) 

21. **Explain the difference between backup of logical and physical database structures**

Physical database backups are a backup of database directories and files (such as data files, data controls and archived logs). The backups should always be stored in a separate, dedicated storage (such as a disk, tape, or in the cloud). This type of backup is useful when you need to restore the complete database within a short period of time. You can have either a full or incremental backup for your physical backup. 

A Logical Backup contains copies of information about a database (such as tables, schemas, and procedures) and are commonly exported out as binary files using EXPORT/ IMPORT tools. If you need to restore or move a copy of the database to another environment (platform) then, logical backups are a great option. 

22. **Discuss the classification of backups (physical structures) according to the save format**

Storage format: 

-  Image copy 
    - An exact copy of a database file 
    - Contains empty blocks 
    - Can be substituted for original file 
- Backup set 
    -  Uses empty block compression 
    - Cannot be used for synthetic full backup

23. **Discuss the classification of backups (physical structures) by content**

- Full backup – all of the data in the backed-up files 
- Incremental backup 
- Level 0 – full backup, but a base for further incremental backups 
- Level 1 cumulative – only blocks changed since last level 0 backup 
- Level 1 – only blocks changed since last incremental backup (level 0 or 1)
- Synthetic full backup – level 0 backup with subsequent level 1 backups applied to it

24. **Discuss the classification of backups (physical structures) in terms of data consistency (what backups can be made in what mode of operation of the database?)**

- Consistent/offline backup 
    - Consistent – stores transaction-consistent data 
    - Offline – turning database offline is required to make consistent backup 
    - Does not require media recovery after restoring original file 
    - Restored file will contain data from the point of making the backup
- Inconsistent/online backup 
    - Inconsistent – stores data in transaction-inconsistent state 
    - Online – can be done while the database is open 
    - Requires media recovery after restoring original file 
    - Restored file will contain data from right before the loss of file 
- Media recovery reapplies changes recorded in the incremental level 1 backups and (archived) redo logs 
    - Media recovery makes restored files consistent and current (by reapplying changes from committed transactions that are not present in the restored file) 
    - Media recovery is only possible in databases in ARCHIVELOG mode

25. Discuss the similarities and differences between the "Point-in-time recovery" and "Flashback database" mechanisms

Point in time recovery works at the physical level to return the data files to their state at a target time in the past. In an RMAN DBPITR operation, you specify a target system change number SCN, log sequence, restore point, or time.

Oracle Database also provides a set of features collectively known as Flashback Technology that supports viewing past states of data, and winding and rewinding data back and forth in time, without requiring the restore of the database from backup.

PRZEROBIC NA SIMILARITIES VS DIFFERENCES

Similarities:

- both enable restoring data to the state of database at some point in time

Differences:

- in PITR you recover to the state at a time but in flashback you can wing and rewind back and forth without restoring database 

26. **List and specify the use of individual flashback mechanisms**

Flashback Query • SELECT … AS OF … - shows data, as it existed in some previous point it time.

Flashback Version Query • VERSIONS BETWEEN { SCN | TIMESTAMP } start AND end – shows different versions of specific rows that existed during a given time interval

Flashback Transaction Query • … FROM flashback_transaction_query… - retrieve historical data for a given transaction or all transactions

Flashback Table • FLASHBACK TABLE … - restores table to a state as of a given point in time 

Flashback Drop • FLASHBACK TABLE … TO BEFORE DROP; - recovers objects from recycle bin

Flashback database • FLASHBACK DATABASE TO… - restore database to a given point in time

27. **Name and characterize automation mechanisms in Oracle**

Stored procedures - program units you can create with PL/SQL and store in the database are standalone procedures and functions, and packages, cursors

Triggers - A special procedure that is launched only by a specified event, Must have: name, database elements that it is triggered for, events that trigger it, trigger type, actions performed by it. 

Oracle Scheduler - Scheduling and automatically triggering events (DBA tasks – Business logic) by time, Three basic components: Schedule – when a task should be performed, Program – actions to be executed (PL/SQL block, stored procedure, Java code), Job – link between Schedule and Program

Automation based on Oracle modules - includes Automatic Storage Management – Flashback – Automatic Workload Repository – Automatic Undo Management – Recovery Manager (???????)

28. **Why is it worthwhile to automate DBA tasks? Which tasks might be automatized and how?**

It is worthwhile to automate because it helps you achieve better reliability, because automated solutions:

- work at night and during weekends,  
- work independently from human administrator (sick/less focused), 
- do not forget to do sth
- repeat actions in exactly same manner 
- do not apply exceptions (apart from programmed ones) 

It can also help with laziness.  If something might be automated, it should be. Automation should not influence instance and database performance (the most effective mechanism should be used. 

Typically automated actions: 

- archiving 
- instance functioning monitoring, incl. performance 
- user actions monitoring, esp. atypical actions 
- alarming about events that compromise reliability and security

29.  List and describe types of triggers in Oracle.

- Triggers on tables (on DML instructions)
    - On INSERT, UPDATE, DELETE actions
    - Types:
        - Before vs After
        - Row level vs instruction level
- Triggers on views (INSTEAD OF)
    -  is defined on non-modifiable view
    - Always on row level
    - Can read :old :new, but cannot change them
- Triggers on system object 
    - Are not related to a view/table 
    - Are launched for actions on the whole database or on schema level

30. **When to use stored procedures? When not to use stored procedures?**

When to use:

- when complex operation can be performed as a whole at server side
    -  no additional information from user app is required
    -  in thin-client case 
- operations on multiple rows should be performed at the strongest node 
    - reduction of network load 
-  when a complex operation is performed periodically or frequently 
    - complex periodical reports eg. daily sale close, monthly sale close 
    - warehouse loading 
    - archiving 
- when a regular operation is composed of multiple steps 
    - creating and setting a regular user account 
- when a composite operation is performed by multiple apps/users many times 
    - Eg. a report used by multiple apps – implemented and tested once at server side 
- Sometimes for access (security) reasons
    - A user might be assigned with a privilege to execute a procedure but not to the source tables

When NOT to use:

- data access complexity increases both for direct users, admins, programmers 
- if a procedure is used by multiple apps and must be changed for one of them 
- when a server is a weak node (thick client)

31. When to use packages? When not to use packages?

When to use? 

- because it has Private methods, variables
- when you have Shared variables and constants among procedures, 
- because they are Loaded to memory as a whole 

When not to create a package? 

- When in a single session you use only one out of all package functions 
- Using them for structuring code is inefficient

32. When to use triggers? When and why not to use them?

When to use?

- for Advanced data correctness 
    - Automatically generated values, 
    - Updating calculated attributes, 
    - Advanced business logic (eg. for performing actions that needs to be done before insert/update of a row – BEFORE triggers) 
    - Advanced check condition – unique value but accepting nulls 
    - Advanced check condition – based on a system variable (eg. sysdate) 
- for Integrity constraints that cannot be imposed in declarative ways 
    - BEFORE trigger + throwing an exception 
    - eg. value of an atrribute cannot be higher/lower/same as a value in another table 
    - eg. a row can reference one table or another (but not both nor any) 
- for Managing integrity in deliberate redundancy
    - Synchronous table replication, 
    - Changes in one table must propagate to other tables, 
    - Advanced business logic
- for Advanced auditing DDL/DML operations 
    - Preventing not allowed operations (that cannot be forced in declarative manner), 
    - Logging for statitical or monitoring purpose 
- for Advanced security mechanisms 
    - Complex authorisation functions – Monitoring users’ activities – Managing security (data access) with a view layer 
- for DBA tasks automation 
    - Reminders, 
    - Atypical error handling (eg. after faulty database logon) 
    - Archiving based on events, – Monitoring for performance/reliablity/security

When NOT to use?

- If the same mechanism (integrity, security…) can be obtained in another built-in way 
    - declarative SQL 
    - special Oracle modules 
- Rule: consider other mechanisms first before adding a trigger 
    - Views, materialized views 
    - NOT NULL, CHECK constraints, DEFAULT values 
    - AUDIT command 

33. Describe costs of using triggers and provide examples how they can be replaced with other mechnisms.

Costs:

- More complex data access 
- Performance drop (esp. for triggers on a row level), 
- Access problems in case of errorneous triggers (for triggers on database level)

Rule: consider other mechanisms first before adding a trigger – Views, materialized views – NOT NULL, CHECK constraints, DEFAULT values – AUDIT command

Examples: ???????

34. Describe main Oracle Scheduler components and relations between them.

Schedule – Schedule specifies frequency and timing of an unspecified action – Single time or periodically – Frequency – To-from dates

Program – Program object specifies a task to be performed – PL/SQL block, stored procedure or function, Java code

Job – link between Schedule and Program, A Job object might be created with no previous definition of Program and Schedule – all the parameters must be specified within a Job 

A program is a separate entity from a job. A job runs at a certain time or because a certain event occurred, and invokes a certain program. A schedule object (schedule) specifies when and how many times a job is run. Schedules can be shared by multiple jobs. One schedule might be used for launching multiple jobs.

35. Optimisation levels in Oracle. Rules for database optimization.

Optimization levels 

- Query and app level 
- Logic database structure level 
- Oracle tuning level 
    - Storage structures optimisation 
    - Instance optimisation (memory, processes, resources) 
- Environment level 
    - Device (disks, operational (physical) memory, processors) 
    - Software (operation system, Oracle version, patches and modules) 
    - Network configuration

Zasady optymalizacji wydajności 

- Praktycznie nigdy nie optymalizujemy z punktu widzenia pojedynczego zapytania, aplikacji, czy użytkownika 
- Istnieje wówczas ryzyko, że naprawiając coś dla pojedynczego zapytania, aplikacji, czy użytkownika, okazuje się, że dla pozostałych zapytań, aplikacji, czy użytkowników wydajność uległa pogorszeniu 
- Zawsze bierzemy pod uwagę różne zapytań, aplikacje i użytkowników, niekoniecznie wszystkich 
- Musimy pamiętać o wszystkich grupach, które można wyróżnić w dostępie do danych

36. Optimisation toolkit in Oracle.

Oracle modules 

- AWR – Automatic Workload Repository - collects, processes, and maintains performance statistics for the database
- ADDM – Automatic Database Diagnostic Monitor - examines and analyzes data captured in the Automatic Workload Repository (AWR) to determine possible performance problems
- TKPROF – TraceKernel Profiler – log analysis - reports each statement executed with the resources it has consumed, the number of times it was called, and the number of rows which it processed

Additional Oracle packages and modules 

- DBMS_STATS – allows to gather statistics for tables 

Oracle advisors 

- Memory Advisors 
- SQL Tuning Advisors 
- SQL Access Advisors 
- Partitioning Advisor 
- SQL Performance Analyzer 

Oracle alerts 

- Alerts are raised by Oracle modules and/or advisors 
- Some are automatic, some have to be turned on intentionally

37. Explain pro-active and action-based (firefighting) optimization in Oracle.

Action optimisation „firefighting” 

- when „Queries are performed slower than before”,  „Query X lasts too long” 
- Analyze performance problem 
    - Ask for detailed information from a user raising the problem: what is too slow (which functions/queries/apps), - when and under what circumstances (is ot repeatable?) - what level of improvement is expected? 
    - Ask other users 
    - Ask: „what changed from the time when it worked better?” 
    - Ask: „is it really necessary to perform this query?” 
    - Use automatic Oracle tools (AWR, ADDM, Oracle Advisors, Top Sessions View, Top SQL View) – analyze proper time frame! 
        - ADDM is said to report 9 out of 10 performance problems before users claim them 
- Look for the root cause – search order? 
    - Queries  -> apps  -> Oracle environment ->  Oracle instance 
- Plan and execute changes – One at a time! 
- Check both the performance changes and instance stability, check apps using database 
    - At test server first, then at production server 
    - Performance improvement must be checked both at test server, and then at production server

Pro-active optimisation 

- PLANNING PERFORMANCE 
- Time-based analysis of instance workload 
    - Workload reduction 
    - Workload balancing (time-based, resource-based) 
    - Parallel workload 
- Identification of queries executed at critical time
    -  v$sql and v$session views 
    - AWR metrics 
    - ADDM alerts 
- Correction of execution plans 
    - Analysing execution plans 
    - Using Oracle advisors 
    - Good practices (eg. Regarding indexes, etc) 
- Checking changes’ influence on performance

38. Explain, how Oracle optimizes SELECT, DML, and COMMIT commands.

SQL – SELECT query processing

4. Parse - analysis

- Looking in previous queries in shared pool (library cache)
- Query syntax control,
- Objects naming control (using data dictionary from Data dictionary cache),
- Blocking objects used in the parse phase
- Access rights control (using data dictionary from Data dictionary cache)
- Creating a query execution plan (action tree)
- Writing down a query and execution plan in Library cache

5. Execute

- Identification of the required records and its location
- Looking for the records in Buffer cache (LRU-least recently used)
- Reading records from datafiles to Buffer cache
- Cursor opening
- Fetch
- Sort

6. Send – from the cursor to the user app (client process)

DML query execution

3. Parse – as in SELECT queries
4. Execution

- Identification of the required records and its location
- Looking for the records in Buffer cache (LRU-least recently used)
- Reading records from datafiles to Buffer cache and additionally to Redo Log Buffer
- Blocking records used in the execution phase
- Modification of the data in Buffer cache (new values)
- Modification of the data status in Redo Log Buffer (old data for rollback)
- „Dirty” block – data in buffer are different from data in physical files

COMMIT query execution

5. Adding an entry with an SCN number in Redo Log Buffer
6.  LGWR process writes down the Redo Log Buffer to Redo Log Files
7. User/app is informed about commit
8. The actual commit entry is written down

39. Goals, methods, and basic operations of the query execution plan in Oracle.

Goals:

- We look for incorrect queries (human errors) 
- We look for optimizer errors (Oracle drawbacks) 
- We look for options to improve performance (Oracle advantages) 

What should raise doubts: – full-scans, for large tables – CARTESIAN JOINS – unselective range scans  index missing? – late predicate filters  changing conditions in where clause? – wrong join order – NESTED LOOPS with large tables, with wrong table order – Non-effective filters

Operations within execution plan 

- Table access methods (stand-alone operations): 
    - Table access full - A full review of the table consisting in sequential retrieval of subsequent rows, until reaching the so-called high-water mark. It is a heavy duty base operation, but its negative impact on performance can be reduced by setting up multi-block read and parallel processing. 
    - Table access by index rowid - Fetching rows by their physical address (ROWID pseudo-column). This access is extremely fast. For this reason, indexes store this address as a kind of pointer to a specific line. 
    - Index unique scan - If unique index is created on the column in the query condition, the optimizer may decide to use it while the query is being processed. Index is a database structure containing ROWID and the content of the column to which it is assigned, stored in such a way as to maximize the search speed. Oracle supports two types of indexes: B-tree and bitmap indexes. 
    - Index range scan - Operation that is performed when the query is based on a range of values or uses a nonunique index. This type of activity requires finding more than one value from the index, therefore they are slower than the index unique scan, and there may be situations where and from table acces full 
    - Hash key access - Access method based on a hash function, i.e. a mathematical transformation that determines the locations of data based on values.

Basic JOIN operations 

- Nested loop 
    - An operation called a nested loop joins the records of two tables in a loop. 
    - Typically, the smaller one uses a full table scan, and for each row, the index of the other table is used to find the matching row. 
    - This operation requires at least two-times access to the data. 
    - Very fast for tables of different sizes when the leading table is small. 
    - Otherwise, be very careful when this operation occurs. 
    - Before executing the query containing such action, it is worth collecting statistics for all participating tables 
- Sort-Merge join 
    - The operation consists of: separate processing and sorting data from each table and then their joining. 
    - The optimizer often performs this when no indexes are available on foreign keys. 
- Hash join 
    - The operation involves creating an auxiliary table (in memory) for the larger of the tables with the values of the hash function on the column with foreign key, and on the other smaller table, performing a full table scan. 
    - Works well when a hashed table can all be created in memory. 
- Cartesian join 
    - Producing an output of each row in one table combined with each row of the second one - very inefficient 
    - Whenever found in execution plan – check correctness of joins in a query

40. Explain the difference between cost-based and rule-based optimizers in the Oracle database.

Rule-based optimizer

- Query execution plan follows the syntax of query 
- More simple to implement 
- Prone to query syntax (order of tables in joins, order of conditions in where clause) 
- Does not take into account the table content characteristics 

Cost-based optimizer 

- Takes into account statistics gathered for table content 
- Takes into account configuration of the database/instance 
- Generates all possible execution plans (different join, where orders) 
- Evaluates cost per each plan using table statistics 
- More complex to implement 
- Less prone to query syntax (order) 
- Might be configured to address some specific goals

41. Indexes - types, when to use, margin selectivity.

An index is an optional structure, associated with a table or table cluster, that can sometimes speed data access.

Optimisation of query might be obtained by: – Creation of an index (proper one!) – Deletion of an index – Index refresh

Types: 

- B-trees:  
    - standard index type
    - excellent for primary key and highly-selective indexes
    - Used as concatenated indexes, B-tree indexes can retrieve data sorted by the indexed columns
- bitmap 
    - an index entry uses a bitmap to point to multiple rows.
    -  In contrast, a B-tree index entry points to a single row.
- Single-column 
    - typical
    - only on one column
- multi-column 
    - composite index, also called a concatenated index, 
    - is an index on multiple columns in a table
    
- Function-based
    - includes columns that are either transformed by a function, such as the UPPER function, or included in an expression.

When:

- The indexed columns are queried frequently and return a small percentage of the total number of rows in the table.
- A referential integrity constraint exists on the indexed column or columns.
- A unique key constraint will be placed on the table and you want to manually specify the index and all index options.
- Use of index makes sense if a query returns LESS than x% of rows in a table 
    - If the result set contains 10k out of 1M or rows (selectivity 1%), index based access will be more efficient 
    - If the result set contains 1 M out of 1M or rows (selectivity 100%), full scan will be more efficient. 
    - 1<x<100% 
    - How to estimate x? (index margin selectivity)
        - The selectivity is the percentage of rows in the table that the query selects, with 0 meaning no rows and 1 meaning all rows.``

42. Explain the difference between query row selectivity and block selectivity. Provide an example.

Row selectivity = number of rows that conform to the query condition to total number of rows in a table 

Block selectivity = number of blocks containing rows that conform to the query condition to total number of blocks containing table rows

EXAMPLE

![](https://lh7-us.googleusercontent.com/wgzIZiTbRtuh5cfw27_R20CLch5kHqtMqAPqh0tJVza_J6CyOMdb4BkEjk0nDZzLCXB6JQCpszuzksK3aw3GnzpQQBIFvUgdprT2rI9IkckX0M8gFYq_DVHySHa782xJ5TymXu-A9GwRadlwNbTSIA)

43. Partitioning in Oracle - types, when to use.

- Supports managing very large tables and indexes by decomposing them into smaller, more manageable parts (partitions)
- Select and DML queries on entire table can work the same as they work for non-partitioned table
- Types:
    - Range Partitioning – based on range of values of an attribute 
        - Frequently used for partitioning based on dates/times eg. partitioning historical from current data
        - Range of values is defined explicitly per each partition
        - Distribution of rows in partitions might be uneven
    - List Partitioning – based on lists of values of an attribute 
        - For a single attribute only 
        - Natural data grouping – conforms with business logic
        - DEFAULT – the rest of rows, if not specified, value other than expected generates an error 
    - Hash Partitioning – based on hash of an attribute 
        - When to use:
            -  For tables that don’t have logical groups 
            - Unknown distribution of data over the ranges 
            - Uneven partition sizes for other criteria 
            - For parallel processing of data (for any ultra-large table)
        - Round-robin algorithm distributes the data evenly in all partitions
    - Composite Partitioning
        - 2 types: RANGE+HASH or RANGE+LIST 
        - RANGE+HASH – logic grouping plus distribution balancing 
        - RANGE+LIST – more detailed logic grouping 
        - Supports: parallel execution, historic data separation, better granularity and data distribution

When to use partitions? 

-  For tables > 2GB partitioning is a must 
- Historical versus current data – consider read-only partitions for historical data, after closing specified period 
- Partition tables where access by different apps/functions considers parts of data only 
- Partition tables that are filled in and queried by different apps/users in a different way 
- In OLAP database consider partitioning for speeding up large reports 

44. Clustering in Oracle - types, when to use.

Clustering – Common storage of data that are used together (although are placed in more tables) – Cluster – a storage structure grouping data coming from different tables 

Purpose: performance improvement – For data that are stored separetely (in 2+ tables) , but used together 

Pros: – Improvement of selected queries performance – More efficient joins 

Cons: – Less efficient DML (updates) – Less options for independent administration and monitoring – Less efficient queries that use a single table out of cluster

Index cluster - default cluster, Oracle stores together rows having the same cluster key value. Each distinct cluster key value is stored only once in each data block, regardless of the number of tables and rows in which it occurs; use indexed clusters in the following cases:

- Your queries retrieve rows over a range of cluster key values.
- Your clustered tables may grow unpredictably.

Hash cluster - Oracle stores together rows that have the same hash key value. The hash value for a row is the value returned by the cluster's hash function. use hash clusters in the following cases:

- Your queries retrieve rows based on equality conditions involving all cluster key columns.
- The tables in the hash cluster are primarily static in size so that you can determine the number of rows and amount of space required for the tables in the cluster.

45. Tools for Oracle performance tuning.

Metrics – Static and dynamic statistical parameters that describe specific domain of instance functioning – eg. Used buffer size, buffer hit ratio, no of read/written blocks, no of concurrent sessions, concurrent SQLs, … 

AWR – Automatic Workload Repository – A repository that could be configured to regularly gather statistics – Time-oriented 

ADDM – Automatic Database Diagnostic Monitor – Detects and reports problems based on AWR repository metrics 

Active Session History (ASH) – Diagnostic tool that records the information about all the active sessions in an Oracle database 

Oracle Advisors – Buffer Cache Advisor, Segment Advisor, Undo Advisor, SQL Access Advisor, … 

Alerts – Generated by Oracle modules or advisors – Usually refer to a metric value eg. Alarm when SYSTEM tablespace X is almost full (98%) – Some alerts are turned on automatically, by default, some other must be set manually

 Views 

46. Metrics and alerts in performance optimisation.

- Metrics 
    - Dynamic statistics on performance – events count from the startup of a database or for a specified period of time - Application statistics (transaction volumes, response time) - Database statistics - Operating system statistics - Disk I/O statistics - Network statistics 
    - Events count from the startup of a database or for a specified period of time 
    - Usually do not inform about how the value changed over time 
    - Time periods for different metrics differ 
    - AWR holds metric values 
    - Dynamic view: v$metric
- Alerts 
    - Server-generated alert is a notification from the Oracle database server of an impending problem 
    - used for monitoring database/instance 
    - Alert is generated when certain parameter/metric exceeds a predefined threshold 
    - DBA may set his owns alerts 
    - Sample automatic alerts 
        - Tablespace usage 
        - Snapshot Too Old 
        - Too little space in Recovery Area 
    - Two types of alerts priority: 
        - Warning 
        - Critical 
    - DBA may define an action for an alert (automatically launched)

47. Views and reports in Oracle performance optimization.

The V$ views are the performance information sources used by all Oracle Database performance tuning tools. The V$ views are based on memory structures initialized at instance startup. The memory structures, and the views that represent them, are automatically maintained by Oracle Database for the life of the instance.

![](https://lh7-us.googleusercontent.com/qqgOso1lP71M2LJN9OexfqFMuuCU4Gb0_TuNw0pqq70V1PRlWyTEAt3lIHzX4aq1pthtw6XzIC4HimHGQFLReC0h3hpigtXlrZB5eATP23BG1DnCb-XyVf0AwvPW_bhwNB_v2vjSS6K_gRivdfZzKA)

48. AWR and ADDM modules, snapshots and baselines - what are they

AWR 

- Automatic repository that gathers data about the instance and database workload; time-based 
- SNAPSHOT (pl. migawka) – „picture” of metrics at a specific moment in time 
    - Default: snapshots of a database states are taken every 60 minutes minut and stored for 7 days
    - Setting interval parameter to 0, stops snapshots taking
- BASELINE – metrics from a period of time (from snapshot to snapshot), used for comparison between periods of workload
    - Setting baselines allows to compare database workload over time
- Types of data gathered: 
    - Blocks and waits 
    - Statistics for SQLs, sessions, users 
    - Active Session History (ASH) statistics from V$ACTIVE_SESSION_HISTORY view 
    - Some statistics of a system and sessions from V$SYSSTAT and V$SESSTAT 
    - Object usage statistics 
    - Top n SQLs
- STATISTICS_LEVEL system parameter sets level of statistics gathering: 
    - BASIC: No advisories or statistics are collected. Monitoring and many automatic features are disabled. Oracle does not recommend this setting because it disables important Oracle Database features 
    - TYPICAL: This is the default value and ensures collection for all major statistics oltwhile providing best overall database performance. This setting should be adequate for most environments 
    - ALL: All of the advisories or statistics that are collected with the TYPICAL setting are included, plus timed operating system statistics and row source execution statistics

Automatic Database Diagnostic Monitor 

- Automatically launched after each AWR metric gathering 
- Detects and reports DB and instance problems 
- Uses AWR repository metrics 
- Alerts raised by ADDM are shown in OEM (web-based) 
- Reviewing ADDM alerts is a quick-run DB monitoring 
- Sometimes provides hints along with an alert

49.  Areas for Oracle optimisation and examples of settings per each area

- Tuning memory (SGA buffers, PGA areas) 
- Tuning storage structures (Local management of extents for tablespaces that contain data, PCTUSED, PCTFREE and INITTRANS parameters adjustment)
- Optimisation of physical I/O operations 
- Re-configuration of instance processes 
- Changing server mode (shared/dedicated, archivelog?) 
- Changing instance parameters (eg. MULTI_BLOCK_READ_COUNT) 
- Workload reduction – Tasks and events reduction – Blocks – User-imposed events and tasks (triggers, jobs) 
- Workload balancing – Resource Plan Management 
- Adjustment of reliability and security mechanisms

50. Differences between OLAP and OLTP databases in terms of performance optimisation.

![](https://lh7-us.googleusercontent.com/YnVNkV_foAqkYE5Hg24MbEwEyy72CpvYx-FPrvV85E5FkLETj16oU--_hyzfHPP3ingS8hZrYyqTFDrD_qf7Wv3JO94X_Ee4qZoqIXTE5Y5OJRWSETmJOyUBh9nR94Fhp5roEl-U12exeHOYII6jHQ)