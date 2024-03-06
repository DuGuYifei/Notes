# QLabel

```cpp
// client
TestLabel* pTestLabel;
/* 显示一段文字 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("显示文字"));
pTestLabel->setGeometry(10, 10, 120, 120);
/* 显示一段文字，左对齐 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("左对齐"));
pTestLabel->setAlignment(Qt::AlignLeft);
pTestLabel->setGeometry(150, 10, 120, 120);
/* 显示一段文字，右对齐 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("右对齐"));
pTestLabel->setAlignment(Qt::AlignRight);
pTestLabel->setGeometry(290, 10, 120, 120);
/* 显示一段文字，上对齐 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("上对齐"));
pTestLabel->setAlignment(Qt::AlignTop);
pTestLabel->setGeometry(430, 10, 120, 120);
/* 显示一段文字，下对齐 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("下对齐"));
pTestLabel->setAlignment(Qt::AlignBottom);
pTestLabel->setGeometry(570, 10, 120, 120);
/* 显示一段文字，设置文字颜色 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("红色文字"));
pTestLabel->setGeometry(10, 150, 120, 120);
pTestLabel->setTextColor(Qt::red);
/* 显示一段文字，设置背景颜色 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("win红色背景"));
pTestLabel->setGeometry(150, 150, 120, 120);
pTestLabel->setWidgetBackColor(Qt::red);
/* 显示一段文字，设置背景颜色 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("label绿色背景(取消)"));
pTestLabel->setGeometry(290, 150, 120, 120);
pTestLabel->setLabelBackColor(Qt::green);
/* 显示一段文字，设置文字大小 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("20大小字体"));
pTestLabel->setGeometry(430, 150, 120, 120);
pTestLabel->setFontSize(20);
/* 显示一段文字，显示控件阴影 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("控件阴影"));
pTestLabel->setGeometry(570, 150, 120, 120);
pTestLabel->setWidgetEffect(Qt::blue);
/* 控件倒圆角 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("控件倒圆角"));
pTestLabel->setGeometry(10, 290, 120, 120);
pTestLabel->setWidgetRound(30);
/* 控件倒圆角+阴影 */
pTestLabel = new TestLabel(this);
pTestLabel->setText(tr("控件倒圆角+阴影"));
pTestLabel->setGeometry(150, 290, 120, 120);
pTestLabel->setWidgetRound(30);
pTestLabel->setWidgetEffect(Qt::gray);
```