# UI

## tkinter
```python
import tkinter as tk
from tkinter import font
import sys
from mocker import LinkedInMocker


class ConsoleDirector:
    def __init__(self, text_widget):
        self.text_widget = text_widget

    def write(self, message):
        self.text_widget.insert(tk.END, message)


class MainPage:
    def __init__(self):
        self.linkedin_mocker = None

        self.submitted_url = ""
        self.root = tk.Tk()
        self.root.title("LinkedIn Auto Filter")
        self.root.geometry("750x600")  # 设置窗口大小

        # self defined font style
        self.font_style = font.Font(family="Helvetica", size=12)

        # Label and Entry for URL input
        self.url_label = tk.Label(self.root, text="URL:", font=self.font_style)
        self.url_label.grid(row=0, column=0, padx=10, pady=10, sticky="w")

        self.url_entry = tk.Entry(self.root, width=50, font=self.font_style, fg='gray')
        self.url_entry.insert(tk.END, "将添加完筛选条件的领英url粘贴到这里")
        self.url_entry.grid(row=0, column=1, padx=10, pady=10, sticky="ew")

        self.url_entry.bind('<FocusIn>', self.on_entry_click)

        # start Button
        self.start_button = tk.Button(self.root, text="Start", command=self.submit_url, font=self.font_style, bg="lightblue")
        self.start_button.grid(row=1, column=0, padx=10, pady=10)

        # Stop Button
        self.stop_button = tk.Button(self.root, text="Stop", command=self.stop_filter, font=self.font_style, bg="salmon")
        self.stop_button.grid(row=1, column=1, padx=10, pady=10, sticky="w")
        self.stop_button.config(state=tk.DISABLED)

        # text box to show information
        self.text_box = tk.Text(self.root, font=self.font_style)
        self.text_box.grid(row=2, column=0, columnspan=2, padx=10, pady=10, sticky="nsew")

        # redirect print to text box
        sys.stdout = ConsoleDirector(self.text_box)
        sys.stderr = ConsoleDirector(self.text_box)

    # bind函数的回调函数
    def on_entry_click(self, event):
        if self.url_entry.get() == "将添加完筛选条件的领英url粘贴到这里":
            self.url_entry.delete(0, tk.END)
            self.url_entry.config(fg='black')

    def submit_url(self):
        self.submitted_url = self.url_entry.get()
        self.start_button.config(state=tk.DISABLED)
        self.stop_button.config(state=tk.NORMAL)
        # create new thread to do this

        self.linkedin_mocker = LinkedInMocker(self.submitted_url)
        self.linkedin_mocker.run()

    def stop_filter(self):
        self.stop_button.config(state=tk.DISABLED)
        self.linkedin_mocker.stop()
        self.start_button.config(state=tk.NORMAL)
        print(self.submitted_url)

```