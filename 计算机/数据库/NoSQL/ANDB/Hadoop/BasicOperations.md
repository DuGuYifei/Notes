# Basic Operations
1. [Login to the Hadoop client machine](#login-to-the-hadoop-client-machine)
2. [上传下载文件从 Hadoop client machine](#上传下载文件从-hadoop-client-machine)
3. [查询时间](#查询时间)
4. [Simple operations on HDFS](#simple-operations-on-hdfs)
   1. [1. 基础命令比如list the content](#1-基础命令比如list-the-content)
   2. [2. 创建自己的文件夹](#2-创建自己的文件夹)
   3. [3. 上传hadoop客户机文件到hdfs文件夹](#3-上传hadoop客户机文件到hdfs文件夹)
   4. [4. 下载hdfs文件到hadoop客户机](#4-下载hdfs文件到hadoop客户机)
   5. [5. 简单的map-reduce任务](#5-简单的map-reduce任务)


## Login to the Hadoop client machine
[ssh](../../../../服务器网络/云服务器操作知识积累/ssh命令连接服务器.md)

## 上传下载文件从 Hadoop client machine
[scp 命令](../../../../服务器网络/云服务器操作知识积累/物理机与虚拟机文件互传.md)

## 查询时间
`hdfs dfs -stat /user/Liu`

## Simple operations on HDFS
### 1. 基础命令比如list the content
   ```bash
   hdfs dfs -ls /
   hdfs dfs -ls /user
   ```
   其实就是加上linux命令，比如删除文件
   ```bash
   hdfs dfs -rm -r -f XXX
   ```
### 2. 创建自己的文件夹
   ```bash
   hdfs dfs -mkdir /user/Liu
   ```
### 3. 上传hadoop客户机文件到hdfs文件夹
   **注意**
   `copyFromLocal`用`./`时会将所有文件包括隐藏文件上传，`./*`将只上传非隐藏文件。
   ```bash
   hdfs dfs -copyFromLocal smalltext.txt /user/Liu/
   ```
   -put 类似
    ```bash
    hdfs dfs -put myfile /user/lada40
    hdfs dfs -cat /user/lada40/myfile
    ```

### 4. 下载hdfs文件到hadoop客户机
   ```bash
   hdfs dfs -copyToLocal /user/Liu/smalltext.txt .
   ```
   -get 类似
    ```bash
    hdfs dfs -get /user/lada40/myfile /path
    ```

### 5. 简单的map-reduce任务
    1. 将Hadoop.jar文件从本机上传到hadoop client machine
    2. 运行命令
       ```bash
       hadoop jar Hadoop1.jar pl.edu.pg.WordCount /user/Liu/smalltext.txt /user/Liu/output
       ```
    3. WordCount的内容是
       1. 新：
        ```java
        package pl.edu.pg;

        import java.io.IOException;
        import java.util.*;

        import org.apache.hadoop.fs.Path;
        import org.apache.hadoop.fs.FileSystem;
        import org.apache.hadoop.conf.*;
        import org.apache.hadoop.io.*;
        import org.apache.hadoop.mapreduce.*;
        import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
        import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
        import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
        import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
        import org.apache.hadoop.util.Tool;
        import org.apache.hadoop.util.ToolRunner;

        public class WordCount extends Configured implements Tool{
        
            public static class Map extends Mapper<LongWritable, Text, Text, IntWritable> {
                private final static IntWritable one = new IntWritable(1);
                private Text word = new Text();

                public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
                    String line = value.toString();
                    StringTokenizer tokenizer = new StringTokenizer(line);
                    while (tokenizer.hasMoreTokens()) {
                        word.set(tokenizer.nextToken());
                        context.write(word, one);
                    }
                }
            }

            public static class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {
            
                public void reduce(Text key, Iterable<IntWritable> values, Context context)
                        throws IOException, InterruptedException {
                    int sum = 0;
                    for (IntWritable val : values) {
                        sum += val.get();
                    }
                    context.write(key, new IntWritable(sum));
                }
            }

            @Override
            public int run(String[] args) throws Exception {
                Job job = Job.getInstance(this.getConf(), "wordcount");

                job.setOutputKeyClass(Text.class);
                job.setOutputValueClass(IntWritable.class);

                job.setJarByClass(WordCount.class);

                job.setMapperClass(Map.class);
                job.setCombinerClass(Reduce.class);
                job.setReducerClass(Reduce.class);

                job.setInputFormatClass(TextInputFormat.class);
                job.setOutputFormatClass(TextOutputFormat.class);

                FileInputFormat.addInputPath(job, new Path(args[0]));
                FileOutputFormat.setOutputPath(job, new Path(args[1]));

                boolean isSuccess = job.waitForCompletion(true);
                return isSuccess ? 0 : 1;
            }

            public static void main(String[] args) throws Exception {
                Configuration conf = new Configuration();
                try{
                    Path fileOutPath = new Path(args[1]);
                    FileSystem fileSystem = FileSystem.get(conf);
                    if (fileSystem.exists(fileOutPath)) {
                        fileSystem.delete(fileOutPath, true);
                    }
                    int status = ToolRunner.run(conf, new WordCount(), args);
                    System.exit(status);
                }catch (Exception e) {
                    e.printStackTrace();
                }
            }

        }
        ```
      1. 旧：
        ```java
        package pl.edu.pg;

        import java.io.IOException;
        import java.util.*;

        import org.apache.hadoop.fs.Path;
        import org.apache.hadoop.conf.*;
        import org.apache.hadoop.io.*;
        import org.apache.hadoop.mapreduce.*;
        import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
        import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
        import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
        import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

        public class WordCount {
        
            public static class Map extends Mapper<LongWritable, Text, Text, IntWritable> {
                private final static IntWritable one = new IntWritable(1);
                private Text word = new Text();

                public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
                    String line = value.toString();
                    StringTokenizer tokenizer = new StringTokenizer(line);
                    while (tokenizer.hasMoreTokens()) {
                        word.set(tokenizer.nextToken());
                        context.write(word, one);
                    }
                }
            }

            public static class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {
            
                public void reduce(Text key, Iterable<IntWritable> values, Context context)
                        throws IOException, InterruptedException {
                    int sum = 0;
                    for (IntWritable val : values) {
                        sum += val.get();
                    }
                    context.write(key, new IntWritable(sum));
                }
            }

            public static void main(String[] args) throws Exception {
                Configuration conf = new Configuration();

                Job job = Job.getInstance(conf, "wordcount");

                job.setOutputKeyClass(Text.class);
                job.setOutputValueClass(IntWritable.class);

                job.setJarByClass(WordCount.class);

                job.setMapperClass(Map.class);
                job.setCombinerClass(Reduce.class);
                job.setReducerClass(Reduce.class);

                job.setInputFormatClass(TextInputFormat.class);
                job.setOutputFormatClass(TextOutputFormat.class);

                FileInputFormat.addInputPath(job, new Path(args[0]));
                FileOutputFormat.setOutputPath(job, new Path(args[1]));

                job.waitForCompletion(true);
            }

        }
        ```
    4. 进阶
        ```bash
        hadoop jar Hadoop2.jar pl.edu.pg.WordCount2 /user/Liu/smalltext.txt /user/Liu/output3 -skip patterns.txt
        ```
        1. patterns.txt
            ```
            \.
            \,
            \!
            to
            ```
        2. WordCount2
            ```java
            package pl.edu.pg;

            import java.io.*;
            import java.util.*;

            import org.apache.hadoop.fs.Path;
            import org.apache.hadoop.conf.*;
            import org.apache.hadoop.io.*;
            import org.apache.hadoop.mapred.*;
            import org.apache.hadoop.util.*;

            public class WordCount2 extends Configured implements Tool {
            
            	public static class Map extends MapReduceBase implements
            			Mapper<LongWritable, Text, Text, IntWritable> {
                        
            		static enum Counters {
            			INPUT_WORDS
            		}

            		private final static IntWritable one = new IntWritable(1);
            		private Text word = new Text();

            		private boolean caseSensitive = true;
            		private Set<String> patternsToSkip = new HashSet<String>();

            		private long numRecords = 0;
            		private String inputFile;

            		public void configure(JobConf job) {
            			caseSensitive = job.getBoolean("wordcount.case.sensitive", true);
            			inputFile = job.get("map.input.file");			

            			if (job.getBoolean("wordcount.skip.patterns", false)) {
            				readPatternsFromConf( job );
            			}
            		}

            		private void readPatternsFromConf(JobConf job) {
            			int patternsNum = job.getInt( "wordcount.skip.patternsNum", 0 );

            			for ( int i = 0; i < patternsNum; i++ ) {
            				patternsToSkip.add( job.get( "wordcount.skip.skipPattern" + Integer.toString( i ) ) );
            			}
            		}

            		public void map(LongWritable key, Text value,
            				OutputCollector<Text, IntWritable> output, Reporter reporter)
            				throws IOException {
            			String line = (caseSensitive) ? value.toString() : value.toString()
            					.toLowerCase();

            			for (String pattern : patternsToSkip) {
            				line = line.replaceAll(pattern, "");
            			}

            			StringTokenizer tokenizer = new StringTokenizer(line);
            			while (tokenizer.hasMoreTokens()) {
            				word.set(tokenizer.nextToken());
            				output.collect(word, one);
            				reporter.incrCounter(Counters.INPUT_WORDS, 1);
            			}

            			if ((++numRecords % 100) == 0) {
            				reporter.setStatus("Finished processing " + numRecords
            						+ " records " + "from the input file: " + inputFile);
            			}
            		}
            	}

            	public static class Reduce extends MapReduceBase implements
            			Reducer<Text, IntWritable, Text, IntWritable> {
            		public void reduce(Text key, Iterator<IntWritable> values,
            				OutputCollector<Text, IntWritable> output, Reporter reporter)
            				throws IOException {
            			int sum = 0;
            			while (values.hasNext()) {
            				sum += values.next().get();
            			}
            			output.collect(key, new IntWritable(sum));
            		}
            	}

            	private Set<String> parseSkipFile(Path patternsFile) {
            		Set<String> patternsToSkip = new HashSet<String>();

            		try {
            			BufferedReader fis = new BufferedReader(new FileReader(
            					patternsFile.toString()));
            			String pattern = null;
            			while ((pattern = fis.readLine()) != null) {
            				patternsToSkip.add(pattern);
            			}
            			fis.close();
            		} catch (IOException ioe) {
            			System.err
            					.println("Caught exception while parsing the file '"
            							+ patternsFile
            							+ "' : "
            							+ StringUtils.stringifyException(ioe));
            		}

            		return patternsToSkip;
            	}

            	public int run(String[] args) throws Exception {
            		JobConf conf = new JobConf(getConf(), WordCount2.class);
            		conf.setJobName("wordcount2");
                            conf.setJarByClass(WordCount2.class );

            		conf.setOutputKeyClass(Text.class);
            		conf.setOutputValueClass(IntWritable.class);

            		conf.setMapperClass(Map.class);
            		conf.setCombinerClass(Reduce.class);
            		conf.setReducerClass(Reduce.class);

            		conf.setInputFormat(TextInputFormat.class);
            		conf.setOutputFormat(TextOutputFormat.class);

            		Set<String> patternsToSkip = new HashSet<String>();

            		List<String> other_args = new ArrayList<String>();
            		for (int i = 0; i < args.length; ++i) {
            			if ("-skip".equals(args[i])) {
            				patternsToSkip.addAll( parseSkipFile( new Path(args[++i]) ) );							
            			} else {
            				other_args.add(args[i]);
            			}
            		}
            		if ( patternsToSkip.size() > 0 ) {
            			conf.setBoolean("wordcount.skip.patterns", true);
            			conf.setInt("wordcount.skip.patternsNum", patternsToSkip.size());
            			Iterator<String> iter = patternsToSkip.iterator(); 
            			for ( int i = 0; i < patternsToSkip.size(); i++ ) {
            				conf.set("wordcount.skip.skipPattern" + Integer.toString( i ), iter.next() );
            			}
            		}

            		FileInputFormat.setInputPaths(conf, new Path(other_args.get(0)));
            		FileOutputFormat.setOutputPath(conf, new Path(other_args.get(1)));

            		JobClient.runJob(conf);
            		return 0;
            	}

            	public static void main(String[] args) throws Exception {
            		int res = ToolRunner.run(new Configuration(), new WordCount2(), args);
            		System.exit(res);
            	}
            }
            ```
    5. output 2 3 输出对比
        ```
        Bye     1
        Goodbye 1
        Hadoop, 1
        Hello   2
        World!  1
        World,  1
        hadoop. 1
        to      1
        ----------------
        Bye     1
        Goodbye 1
        Hadoop  1
        Hello   2
        World   2
        hadoop  1
        ```