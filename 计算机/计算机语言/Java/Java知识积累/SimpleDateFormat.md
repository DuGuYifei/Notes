# SimpleDateFormat

```java
SimpleDateFormat frmtIn = new SimpleDateFormat("MM/dd/yyyy HH:mm"); 
Date appointmentDate = frmtIn.parse(fields[11]); 

private long getDateDiff(Date end, Date start) { 
	long diffInMillies = end.getTime() - start.getTime(); 
	TimeUnit tu = TimeUnit.MINUTES; 
	return tu.convert(diffInMillies, TimeUnit.MILLISECONDS); 
} 


SimpleDateFormat frmtOut = new SimpleDateFormat("HH"); 
int hour = Integer.parseInt(frmtOut.format(appointmentDate)); 
```