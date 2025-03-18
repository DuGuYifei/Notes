# xml文件读写

[c# 操作xml文件（读写） - 大海的泡沫 - 博客园](https://www.cnblogs.com/likui-bookHouse/p/11132756.html)

```c#
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace iImgEnh.UI.AuthenticateImage.AuthImageMethods.Model
{
    public class VideoContinuityReadWriteRecord
    {
        #region 属性
        /// <summary>
        /// 存放xml内容的文件夹下的文件名
        /// </summary>
        private string DicFileName = "resources/XMLFile.xml";

        #endregion

        #region 写入xml
        /// <summary>
        ///
        /// </summary>
        /// <param name="file"></param>
        /// <param name="content"></param>
        /// <param name="dateTimeStr"></param>
        public void WriteDoc(string file,string content,string dateTimeStr)
        {
            string SavePath = Path.Combine(Directory.GetCurrentDirectory(), "resources");

            //判断是否存在文件夹
            var DirectoryPath = Path.GetDirectoryName(SavePath);  //获取文件夹所在的路径
            if (!Directory.Exists(SavePath))
            {
                Directory.CreateDirectory(SavePath);  //创建文件夹
            }
            XmlDocument doc = new XmlDocument();
            if (File.Exists(DicFileName))
            {
                //如果文件存在 加载XML
                doc.Load(DicFileName);
                //获得文件的根节点
                XmlNodeList xnl = doc.SelectNodes("/Positions/Position/Item");
                if (xnl.Count < 1)
                {
                   CreateDoc(file, content,dateTimeStr);
                }
                else
                {
                    XmlNode PNode = null;
                    var isHave = false;
                    foreach (XmlNode item in xnl)
                    {
                        PNode = item.ParentNode;
                        var name = item.Attributes["Name"].Value;
                        //var text = item.Attributes["Content"].Value;
                        if (name == file)
                        {
                            isHave = true;
                            item.Attributes["Content"].Value = content;
                            item.Attributes["Time"].Value = dateTimeStr;
                            break;
                        }
                    }
                    if (!isHave)
                    {
                        var en = doc.DocumentElement;
                        XmlElement name1 = doc.CreateElement("Item");
                        name1.SetAttribute("Name", file);
                        name1.SetAttribute("Content", content);
                        name1.SetAttribute("Time", dateTimeStr);
                        PNode.AppendChild(name1);

                        if (xnl.Count > 20)
                        {
                            PNode.RemoveChild(xnl[0]);
                        }

                    }
                }
                doc.Save(DicFileName);
            }
            else
            {
                CreateDoc(file, content,dateTimeStr);
            }
        }

        /// <summary>
        /// 读取XML文件
        /// </summary>
        /// <param name="file"></param>
        /// <returns></returns>
        public RecordInfo ReadDoc(string file)
        {
            RecordInfo info = new RecordInfo();
            XmlDocument doc = new XmlDocument();
            if (File.Exists(DicFileName))
            {
                //如果文件存在 加载XML
                doc.Load(DicFileName);
                //获得文件的根节点
                XmlNodeList xnl = doc.SelectNodes("/Positions/Position/Item");
                if (xnl.Count > 0)
                {
                    foreach (XmlNode item in xnl)
                    {
                        if (item.Attributes["Name"].Value == file)
                        {
                            info.Position = item.Attributes["Content"].Value;
                            info.Time = item.Attributes["Time"].Value;
                        }
                    }
                }
            }
            return info;
        }

        /// <summary>
        /// 创建XML文件
        /// </summary>
        /// <param name="file"></param>
        /// <param name="content"></param>
        /// <param name="dateTimeStr"></param>
        private void CreateDoc(string file, string content,string dateTimeStr)
        {
            XmlDocument doc = new XmlDocument();
            //3、创建第一个行描述信息，并且添加到doc文档中
            XmlDeclaration dec = doc.CreateXmlDeclaration("1.0", "utf-8", null);
            doc.AppendChild(dec);
            //4、创建根节点
            XmlElement books = doc.CreateElement("Positions");
            //将根节点添加到文档中
            doc.AppendChild(books);

            //5、给根节点Books创建子节点
            XmlElement book1 = doc.CreateElement("Position");
            //将book添加到根节点
            books.AppendChild(book1);
            //6、给Book1添加子节点
            XmlElement name1 = doc.CreateElement("Item");
            name1.SetAttribute("Name", file);
            name1.SetAttribute("Content", content);
            name1.SetAttribute("Time", dateTimeStr);
            book1.AppendChild(name1);

            doc.Save(DicFileName);
        }

        #endregion
    }

    public class RecordInfo
    {
        /// <summary>
        /// 位置
        /// </summary>
        public string Position { get; set; }

        /// <summary>
        /// 时间格式
        /// </summary>
        public string Time { get; set; }
    }
}
```