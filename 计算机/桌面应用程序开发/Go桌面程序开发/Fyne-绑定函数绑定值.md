# Fyne-绑定函数绑定值

```go
package console

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
	"go_client/cache"
	"strings"
	"sync"

	log "github.com/cihub/seelog"
)

var (
	allUserList       *fyne.Container
	latestUserList    *fyne.Container
	searchUserList    *fyne.Container
	tabs              *container.AppTabs
	allUserScrollVBox *container.Scroll
	latestScrollVBox  *container.Scroll
	UIMutex           sync.Mutex
	latestMutex       sync.Mutex
)

func createUserInfoList() {
	clearBannedUsernamesFromTXT()
	items := cache.NicknameIsBannedCache.Items()
	for k, v := range items {
		userCache := v.Object.(*cache.UserCache)
		log.Info(userCache.Nickname)
		targetNickname := userCache.Nickname
		if targetNickname == "" {
			targetNickname = strings.Split(k, ":")[2]
		}
		checkButton := widget.NewCheckWithData(targetNickname, userCache.Banned)
		checkButton.OnChanged = func(on bool) {
			if on {
				checkButton.SetText(targetNickname + "(屏蔽)")
				log.Info("屏蔽用户" + targetNickname)
				log.Debug("alluserlist更新")
				go writeBannedUsernameToTXT(targetNickname)
			} else {
				checkButton.SetText(targetNickname)
				log.Debug("alluserlist更新2")
				log.Info("解除屏蔽用户" + targetNickname)
				go deleteBannedUsernameFromTXT(targetNickname)
			}
			userCache.Banned.Set(on)
		}
		userItem := container.NewHBox(checkButton)
		allUserList.Add(userItem)
	}
}

func AddUserInfoList(key string, userCache *cache.UserCache) {
	targetNickname := userCache.Nickname
	if targetNickname == "" {
		targetNickname = strings.Split(key, ":")[2]
	}
	checkButton := widget.NewCheckWithData(targetNickname, userCache.Banned)
	checkButton.OnChanged = func(on bool) {
		if on {
			checkButton.SetText(targetNickname + "(屏蔽)")
			log.Info("屏蔽用户" + targetNickname)
			go writeBannedUsernameToTXT(targetNickname)
		} else {
			checkButton.SetText(targetNickname)
			log.Info("解除屏蔽用户" + targetNickname)
			go deleteBannedUsernameFromTXT(targetNickname)
		}
		userCache.Banned.Set(on)
	}
	userItem := container.NewHBox(checkButton)
	allUserList.Add(userItem)
	allUserScrollVBox.Refresh()
	latestScrollVBox.Refresh()
}

func updateFilteredList(filter string) {
	allUserScrollVBox.Content = searchUserList
	searchUserList.Objects = nil
	for _, userItem := range allUserList.Objects {
		if strings.Contains(userItem.(*fyne.Container).Objects[0].(*widget.Check).Text, filter) {
			searchUserList.Add(userItem)
		}
	}
	allUserScrollVBox.Refresh()
}

func recoverFilteredList() {
	allUserScrollVBox.Content = allUserList
	allUserScrollVBox.Refresh()
}

func UpdateLatestUserList(key string) {
	latestMutex.Lock()
	defer latestMutex.Unlock()
	if cache.AddLatestUserCache(key) != true {
		return
	}
	latestUserList.Objects = nil
	for _, userCache := range cache.LatestNicknameIsBannedQueue {
		targetNickname := userCache.Nickname
		if targetNickname == "" {
			targetNickname = strings.Split(key, ":")[2]
		}
		checkButton := widget.NewCheckWithData(targetNickname, userCache.Banned)
		checkButton.OnChanged = func(on bool) {
			if on {
				checkButton.SetText(targetNickname + "(屏蔽)")
				log.Info("屏蔽用户" + targetNickname)
			} else {
				checkButton.SetText(targetNickname)
				log.Info("解除屏蔽用户" + targetNickname)
			}
			userCache.Banned.Set(on)
		}
		userItem := container.NewHBox(checkButton)
		latestUserList.Add(userItem)
	}
	latestScrollVBox.Refresh()
	allUserScrollVBox.Refresh()
}

func RunWindow() {
	myApp := app.New()

	myWindow := myApp.NewWindow("用户管理")
	latestUserList = container.NewVBox()
	searchUserList = container.NewVBox()
	allUserList = container.NewVBox()
	tabs = container.NewAppTabs()
	allUserScrollVBox = container.NewVScroll(allUserList)
	allUserScrollVBox.SetMinSize(fyne.NewSize(400, 620))
	latestScrollVBox = container.NewVScroll(latestUserList)
	latestScrollVBox.SetMinSize(fyne.NewSize(400, 640))

	createUserInfoList()
	searchEntry := widget.NewEntry()
	searchEntry.SetPlaceHolder("搜索用户昵称...")
	searchEntry.OnSubmitted = func(content string) {
		updateFilteredList(content)
	}
	searchEntry.OnChanged = func(content string) {
		if content == "" {
			recoverFilteredList()
		}
	}
	allUserTab := container.NewVBox(searchEntry, allUserScrollVBox)
	// 创建标签页容器
	tabs.Append(container.NewTabItem("最新用户", latestScrollVBox))
	tabs.Append(container.NewTabItem("所有用户", allUserTab))

	myWindow.SetContent(tabs)
	myWindow.Resize(fyne.NewSize(400, 700))
	myWindow.ShowAndRun()
}
```