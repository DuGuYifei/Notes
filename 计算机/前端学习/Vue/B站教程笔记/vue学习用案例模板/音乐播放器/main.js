/*
  1:歌曲搜索接口
    请求地址:https://autumnfish.cn/search
    请求方法:get
    请求参数:keywords(查询关键字)
    响应内容:歌曲搜索结果
  2:歌曲url获取接口
    请求地址:https://autumnfish.cn/song/url
    请求方法:get
    请求参数:id(歌曲id)
    响应内容:歌曲url地址
  3.歌曲详情获取
    请求地址:https://autumnfish.cn/song/detail
    请求方法:get
    请求参数:ids(歌曲id)
    响应内容:歌曲详情(包括封面信息)
  4.热门评论获取
    请求地址:https://autumnfish.cn/comment/hot?type=0
    请求方法:get
    请求参数:id(歌曲id,地址中的type固定为0)
    响应内容:歌曲的热门评论
  5.mv地址获取
    请求地址:https://autumnfish.cn/mv/url
    请求方法:get
    请求参数:id(mvid,为0表示没有mv)
    响应内容:mv的地址
*/

var app = new Vue({
    el: "#player",
    data: {
        query: "",
        musicList: [],
        musicUrl: "",
        musicCover: "",
        musicComment: "",
        mvUrl: "",
        isPlaying: false,
        isShow: false,
        lyric:[],
        singleLyric:"",
        singleLyric_prev:"",
        singleLyric_next:"",
    },
    methods: {
        searchMusic: function () {
            var that = this;
            axios.get("https://autumnfish.cn/search?keywords=" + this.query)
                .then(
                    function (response) {
                        that.musicList = response.data.result.songs;
                    },
                    function (err) { }
                )
        },
        playMusic(id) {
            var that = this;
            axios.get("https://autumnfish.cn/song/url?id=" + id)
                .then(function (response) {
                    that.musicUrl = response.data.data[0].url;
                }, function (err) { });
            axios.get("https://autumnfish.cn/song/detail?ids=" + id)
                .then(function (response) {
                    that.musicCover = response.data.songs[0].al.picUrl;
                }, function (err) { });
            axios.get('https://autumnfish.cn/comment/hot?type=0&id=' + id)
                .then(function (response) {
                    that.musicComment = response.data.hotComments;
                }, function (err) { });
            axios.get('https://autumnfish.cn//lyric?id=' + id)
                .then(function(response){
                    //console.log(response.data.lrc.lyric);
                    let rows = response.data.lrc.lyric.split('\n');
                    rows.forEach(element => {
                        let index = element.indexOf(':');
                        let min = element.slice(1, index);
                        let index2 = element.indexOf(']');
                        let sec = element.slice(index + 1, index2);
                        let word = element.slice(index2 + 1);
                        let time = min * 60 + (+sec);
                        that.lyric.push([time, word]);
                    });
                    //console.log(that.lyric);
                    that.lyric.index = 0;
                    that.singleLyric = that.lyric[0][1];
                    if(that.lyric.length > 1)
                    {
                        that.singleLyric_next = that.lyric[1][1];
                    }
                })
        },
        play() {
            //console.log(document.getElementById("audioPlay").currentTime);
            //console.log(document.getElementById("audioPlay").duration);

            this.isPlaying = true;
            let audio = document.getElementById("audioPlay");
            this.lyric.timerId = setInterval(() => {
                if(audio.currentTime < 1)
                {
                    this.lyric.index = 0;
                    this.singleLyric = this.lyric[0][1];
                    this.singleLyric_next = this.lyric[1][1];
                    this.singleLyric_prev = " ";
                }
                if(this.lyric.index < this.lyric.length - 1)
                {
                    //console.log(audio.currentTime);
                    if(audio.currentTime > this.lyric[this.lyric.index + 1][0])
                    {
                        while(audio.currentTime > this.lyric[this.lyric.index + 1][0])
                        {
                            this.lyric.index++;
                        }
                        while(audio.currentTime < this.lyric[this.lyric.index][0])
                        {
                            this.lyric.index--;
                        }
                        this.singleLyric_prev = this.lyric[this.lyric.index - 1][1];
                        this.singleLyric = this.lyric[this.lyric.index][1];
                        if(this.lyric.index + 1 < this.lyric.length)
                        {
                            this.singleLyric_next = this.lyric[this.lyric.index + 1][1];
                        }
                        else
                        {
                            this.singleLyric_next = " ";
                        }
                        //console.log(this.singleLyric);
                    }
                }
                else if(this.lyric.index == this.lyric.length - 1)                
                {
                    this.lyric.index = 0;
                }
            }, 500);
        },
        pause() {
            this.isPlaying = false;
            clearInterval(this.lyric.timerId);
        },
        playMV(mvid) {
            var that = this;
            this.isShow = true;
            axios.get("https://autumnfish.cn/mv/url?id=" + mvid)
                .then(function (response) {
                    that.mvUrl = response.data.data.url;
                }, function (err) { })
        },
        hide() {
            this.isShow = false;
        }

    }
});