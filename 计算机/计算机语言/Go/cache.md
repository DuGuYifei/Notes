# cache

```go
"github.com/patrickmn/go-cache"

var userInfoCache = cache.New(cache.NoExpiration, 0)
var talkCache = cache.New(config.TalkCacheTimeout*time.Second, 0)

func getNickname(clientId int, searchWxid string) (string, error) {
	var base = "user_info:identifier:%s"
	key := fmt.Sprintf(base, searchWxid)
	item, found := userInfoCache.GetItem(key, true)
	if found {
		return item.Object.(dtowxresponseme.JsonUserInfo).Nickname, nil
	}
	userInfo, err := GetUserInfo(clientId, searchWxid)
	if err != nil {
		return "", err
	}
	userInfoCache.Set(key, userInfo, cache.DefaultExpiration)
	return userInfo.Nickname, nil
}

func checkIsAbleSendByTalkCache(clientId int, receiverWxid string, newMsg string) (string, bool) {
	var base = "talk:identifier:%s-%s"
	key := fmt.Sprintf(base, strconv.Itoa(clientId), receiverWxid)
	item, found := talkCache.GetItem(key, true)
	if found {
		msg := item.Object.(string) + newMsg
		if time.Now().UnixNano() > item.Expiration {
			talkCache.Delete(key)
			return msg, true
		} else {
			talkCache.Set(key, msg, cache.DefaultExpiration)
			return "", false
		}
	}
	talkCache.Set(key, newMsg, cache.DefaultExpiration)
	return "", false
}
```