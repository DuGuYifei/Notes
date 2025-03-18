# ArrayWritable

## 问题

* 不能直接使用，要构建自己类 IntArrayWritable 等

## 写入文件 toString
```java
	public static class DoubleArrayWritable extends ArrayWritable {
		public DoubleArrayWritable() {
			super(DoubleWritable.class);
		}
		public DoubleArrayWritable(DoubleWritable[] arr){
			super(DoubleWritable.class, arr);
		}

		@Override
		public String toString() {
			String res = "";
			for(DoubleWritable dw : (DoubleWritable[])get()){
				res = res + " " + dw.get();
			}
			return res;
		}
	}
```

## 如何从map到redduce

```java
	public static class IntArrayWritable extends ArrayWritable {
		public IntArrayWritable() {
			super(IntWritable.class);
		}
		public IntArrayWritable(IntWritable[] arr){
			super(IntWritable.class, arr);
		}
	}
 	public static class TopLinksReduce extends Reducer<NullWritable, IntArrayWritable, IntWritable, IntWritable> {
        private Integer N;
        private TreeSet<ComparablePair<Integer, Integer>> countToIdMap = new TreeSet<>();

        @Override
        protected void setup(Context context) throws IOException,InterruptedException {
            Configuration conf = context.getConfiguration();
            this.N = conf.getInt("N", 10);
        }

        @Override
        public void reduce(NullWritable key, Iterable<IntArrayWritable> values, Context context) throws IOException, InterruptedException {

            for (IntArrayWritable val : values) {
                IntWritable[] pair = (IntWritable[]) val.toArray();
                Integer id = pair[0].get();
                Integer count = pair[1].get();
                countToIdMap.add(new ComparablePair<Integer, Integer>(count, id));
            }
            if (countToIdMap.size() > N) {
                countToIdMap.remove(countToIdMap.first());
            }
        }
	}
```