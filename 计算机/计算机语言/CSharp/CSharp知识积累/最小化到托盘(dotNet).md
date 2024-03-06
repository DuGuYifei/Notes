# 最小化到托盘(dotNet)

- 添加notifyIcon控件
- 添加contextMenuStrip控件
- 第二条控件添加退出
- 在notifyIcon的属性ContextMenuStrip中选择第二条
- 代码
  ```c#
  //双击显示
        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.WindowState = FormWindowState.Normal;
                this.ShowInTaskbar = true;
            }
        }
  //关闭按钮重写
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //取消关闭窗口
            e.Cancel = true;
            //最小化主窗口
            this.WindowState = FormWindowState.Minimized;
            //不在系统任务栏显示主窗口图标
            this.ShowInTaskbar = false;
            //提示气泡
            this.notifyIcon1.ShowBalloonTip(3000, "最小化到托盘", "程序已经缩小到托盘，双击打开程序。", ToolTipIcon.Info);
        }
  //退出程序（contextMenuStrip中的退出）
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //this.notifyIcon1.Visible = false;

            System.Diagnostics.Process.Start("WallpaperEngine.exe", "q");
            
            this.Dispose(true);
            this.Close();
        }

  ```