# 创建xlsx

1. `XSSFWorkbook`是xlsx
2. `XSSFSheet`是一页
3. `Row`是一行
4. `Cell`是一个单元格
5. `XSSFDrawing`是画图
6. `XSSFClientAnchor`是锚点
7. `XSSFChart`是图表 和 Drawing区别是什么？
   1. Drawing是画图，Chart是图表
   2. Drawing是一个sheet里面只能有一个，Chart是一个sheet里面可以有多个

```java
  public Workbook generateReport(
      GenerateReportDto dto,
      Map<Integer, String> resultLongest,
      Map<Integer, String> resultShortest,
      int iterations) {
    int numThreads = dto.getNumThreads();
    XSSFWorkbook workbook = new XSSFWorkbook();
    XSSFSheet longestSpreadsheet = workbook.createSheet(
        "Analysis - Longest Logs");

    Row rowLongest = longestSpreadsheet.createRow((short) 0);
    Cell cellLongest = rowLongest.createCell((short) 0);
    cellLongest.setCellValue("Threads number");
    cellLongest = rowLongest.createCell((short) 1);
    cellLongest.setCellValue("Time(ms) - Average, measured for: " + iterations + " iterations");

    for (int i = 1; i <= numThreads; i++) {
      rowLongest = longestSpreadsheet.createRow((short) i);
      cellLongest = rowLongest.createCell((short) 0);
      cellLongest.setCellValue(i);
      cellLongest = rowLongest.createCell((short) 1);
      cellLongest.setCellValue(Integer.parseInt(resultLongest.get(i)));
    }

    XSSFDrawing drawingLongest = longestSpreadsheet.createDrawingPatriarch();
    XSSFClientAnchor anchorLongest = drawingLongest.createAnchor(0, 0, 0, 0, 4, 0, 18, 25);

    XSSFChart chartLongest = drawingLongest.createChart(anchorLongest);
    chartLongest.setTitleText("Analysis of threads number performance (longest)");
    chartLongest.setTitleOverlay(false);

    XDDFChartLegend legend = chartLongest.getOrAddLegend();
    legend.setPosition(LegendPosition.TOP_RIGHT);

    XDDFCategoryAxis bottomAxisLongest = chartLongest.createCategoryAxis(AxisPosition.BOTTOM);
    bottomAxisLongest.setTitle("Threads number");
    XDDFValueAxis leftAxisLongest = chartLongest.createValueAxis(AxisPosition.LEFT);
    leftAxisLongest.setTitle("Duration time(ms) - average");

    XDDFDataSource<String> threadsLongest = XDDFDataSourcesFactory.fromStringCellRange(
        longestSpreadsheet,
        new CellRangeAddress(1, numThreads, 0, 0));

    XDDFNumericalDataSource<Double> timeLongest = XDDFDataSourcesFactory.fromNumericCellRange(
        longestSpreadsheet,
        new CellRangeAddress(1, numThreads, 1, 1));

    XDDFLineChartData data = (XDDFLineChartData) chartLongest.createData(
        ChartTypes.LINE,
        bottomAxisLongest,
        leftAxisLongest);

    XDDFLineChartData.Series series1Longest = (XDDFLineChartData.Series) data.addSeries(
        threadsLongest,
        timeLongest);
    series1Longest.setTitle("Duration", null);
    series1Longest.setSmooth(false);
    series1Longest.setMarkerStyle(MarkerStyle.STAR);

    chartLongest.plot(data);

    XSSFSheet shortestSpreadsheet = workbook.createSheet(
        " Analysis - Shortest Logs ");

    Row rowShortest = shortestSpreadsheet.createRow((short) 0);
    Cell cellShortest = rowShortest.createCell((short) 0);
    cellShortest.setCellValue("Threads number");
    cellShortest = rowShortest.createCell((short) 1);
    cellShortest.setCellValue("Time(ms) - Average, measured for: " + iterations + " iterations");
    for (int i = 1; i <= numThreads; i++) {
      rowShortest = shortestSpreadsheet.createRow((short) i);
      cellShortest = rowShortest.createCell((short) 0);
      cellShortest.setCellValue(i);
      cellShortest = rowShortest.createCell((short) 1);
      cellShortest.setCellValue(Integer.parseInt(resultShortest.get(i)));
    }

    XSSFDrawing drawingShortest = shortestSpreadsheet.createDrawingPatriarch();
    XSSFClientAnchor anchorShortest = drawingShortest.createAnchor(
        0,
        0,
        0,
        0,
        4,
        0,
        18,
        25);

    XSSFChart chartShortest = drawingShortest.createChart(anchorShortest);
    chartShortest.setTitleText(
        "Analysis of threads number performance (shortest)");
    chartShortest.setTitleOverlay(false);

    XDDFChartLegend legendShortest = chartShortest.getOrAddLegend();
    legendShortest.setPosition(LegendPosition.TOP_RIGHT);

    XDDFCategoryAxis bottomAxisShortest = chartShortest.createCategoryAxis(
        AxisPosition.BOTTOM);
    bottomAxisShortest.setTitle("Threads number");
    XDDFValueAxis leftAxisShortest = chartShortest.createValueAxis(
        AxisPosition.LEFT);
    leftAxisShortest.setTitle("Duration time(ms) - average");

    XDDFDataSource<String> threadsShortest = XDDFDataSourcesFactory.fromStringCellRange(
        shortestSpreadsheet,
        new CellRangeAddress(1, numThreads, 0, 0));

    XDDFNumericalDataSource<Double> timeShortest = XDDFDataSourcesFactory.fromNumericCellRange(
        shortestSpreadsheet,
        new CellRangeAddress(1, numThreads, 1, 1));

    XDDFLineChartData dataShortest = (XDDFLineChartData) chartShortest.createData(
        ChartTypes.LINE,
        bottomAxisShortest,
        leftAxisShortest);

    XDDFLineChartData.Series series1Shortest = (XDDFLineChartData.Series) dataShortest.addSeries(
        threadsShortest,
        timeShortest);
    series1Shortest.setTitle("Duration", null);
    series1Shortest.setSmooth(false);
    series1Shortest.setMarkerStyle(MarkerStyle.STAR);

    chartShortest.plot(dataShortest);

    return workbook;
  }
```