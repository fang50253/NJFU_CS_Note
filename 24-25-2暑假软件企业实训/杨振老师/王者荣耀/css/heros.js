 // 下载浮窗
 var d_open='<div class="down_detail" exposure-tag="down_detail,内页下载浮窗"><div class="d_open"><img class="d_qrcode"  src="https://game.gtimg.cn/images/yxzj/web201706/images/comm/floatwindow/wzry_qrcode.jpg" width="107" height="107"  alt="下载游戏"/> </div></div> ';
 var openDiv=document.createElement('div');
 openDiv.innerHTML=d_open;
 document.body.appendChild(openDiv);
$(function() {
    // 设置英雄职业图标 Start
    var $heroSort = $('#hero-sort');
    if($heroSort && $heroSort.data('sort')) {
        var heroSortHtml = ''
        $.each(($heroSort.data('sort')+'').split('|'),function(index,value){
            heroSortHtml+='<i class="hero-sort hero-sort-'+value+'"></i>';
       });
       $heroSort.html(heroSortHtml);
    }
    // 设置英雄职业图标 End
    $('.hero-skill-intro .skill-list li').on('mouseenter', function() {
        $(this).addClass('on');
        $(this).siblings().removeClass('on');
        $(this).parent().parent().siblings('.skill-cont').find('.skill-cont-list').removeClass('on');
        $(this).parent().parent().siblings('.skill-cont').find('.skill-cont-list').eq($(this).index()).addClass('on');
    })
    $(window).scroll(function(event) {
        $('.sub-header').addClass('scrollDis');
        if ($(window).scrollTop() <= 90) {
            $('.sub-header').removeClass('scrollDis');
        }
    });
    //锚点跳转滑动效果  
    $('.sub-list li a[href*=#],area[href*=#],.info-tab a[href*=#]').click(function() {
        $(this).parent('li').siblings().removeClass('on');
        $(this).parent('li').addClass('on');
        if (location.pathname.replace(/^\//, '') == this.pathname.replace(/^\//, '') && location.hostname == this.hostname) {
            var $target = $(this.hash);
            $target = $target.length && $target || $('[name=' + this.hash.slice(1) + ']');
            if ($target.length) {
                var targetOffset = $target.offset().top;
                $('html,body').animate({
                    scrollTop: targetOffset
                }, 500);
                return false;
            }
        }
    });

    //2020年7月6日 新增视频弹窗
    function TGDialogS(e){
        // 利用milo库引入dialog组件
        need("biz.dialog",function(Dialog){
            Dialog.show({
                id:e,
                bgcolor:'#000', //弹出“遮罩”的颜色，格式为"#FF6600"，可修改，默认为"#fff"
                opacity:70 //弹出“遮罩”的透明度，格式为｛10-100｝，可选
            });
        });
    }
    function closeDialog(){
        // 利用milo库引入dialog组件
        need("biz.dialog",function(Dialog){
            Dialog.hide();
        });
    }

    // 播放视频
    var player;
    $("body").on("click", ".player-box", function() {
        var _self = $(this).parent(),
            vid = _self.data("vid")
        if (vid) {
            player = new Txplayer({
                containerId: 'video-box',
                vid: vid,
                width: '100%',
                height: '100%',
                autoplay: true,
                platform: '8330701',
	  	        sdtfrom: 'v7102',
            });
            TGDialogS('dialog-video');
        }
    })

    //关闭视频
    $('#dialog-video .dia-close').on('click',function () {
        player.pause();
        showDialog.hide();
    });
    //2020年7月6日 新增视频弹窗 End


    //播放英雄语音
    var voice = document.getElementById('voice');
    $('#heroVoice .voice-list').on('click','li',function () {
        var voiceSrc = $(this).attr('data-voice');
        $('.voice-list').find('li').removeClass('active');
        $(this).addClass('active');
        $('#voice').attr('src',voiceSrc);
        voice.play();
    });

    //玩法思路swiper
    var thinking = new Swiper('.thinking-swiper', {
        loop:true,
        observer:true,
        observeParents:true,
  pagination: {
      el: '.swiper-pagination',
    },
    autoplay: {
    delay: 5000,//1秒切换一次
  }
    });
})

// 英雄印象
var heroImpression = (function () {
    var curPage = 0,
        url = {
            black : "//uic.gamesafe.qq.com/uiccgi.cgi",
            add: "//app.ingame.qq.com/php/ingame/interactcenter/add_tiny_guide.php",
            query: "//app.ingame.qq.com/php/ingame/interactcenter/query_tiny_guide_by_id.php",
            vote: "//app.ingame.qq.com/php/ingame/interactcenter/add_tiny_guide_vote.php",
            sub:"" //登录态暂存
        },
        param = {
            game : 'smoba', //游戏英文缩写(例如欢乐斗地主：poker)
            bid : 'ingame', //业务英文缩写
            channel: 1,     //渠道ID(1:微社区；2：手游乐园；3：同人站)
            order_type: 2, //排序类型(1:发布时间 2:威尔逊置信区间排序)
            sandbox: 0,     // 测试环境沙盒(1:测试环境 0:正式环境)
            works_id:''     // heroid
        },
        selector = {
            input : "#impressionTxt",
            submit : "#impressionSubmit",
            show: "div.impression-show",
            list:"ul.impression-list",
            more: "a.a-toggle-more",
            hide: "a.a-toggle-hide"
        },
        fn = {},
        util = {},
        init = function () { };
    
    // 获取登录态
    fn.getOpenid = function (userinfo) {
        if (url.sub) { 
            var r = url.sub;
        }else if (userinfo && userinfo.logtype == "wx") {
            var r = "?appid=wx95a3a4d7c627e07d&login_type=wxm&access_token=" + milo.cookie.get("access_token") + "&openid=" + userinfo.openid;
        }else{
            var r = "?appid=1104466820&login_type=qqm&skey="+milo.cookie.get('skey')+"&uin="+milo.cookie.get('uin');
        }
        return r;
    }
    // 检查登录
    util.checkLogin = function () {
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                // alert("您已登录，可以直接提交");
                return true;
            }, function () {
                alert("登录后才能提交英雄印象标签！");
                TGDialogS('login_select');
                return false;
                // qqAndwxLoginout();
            });
        });
    }
    // 查询标签
    util.queryImpress = function (heroId,gStart,gNum) {
        if(!heroId){return}
        var gNum = gNum || 10, gStart = gStart || 0;
        PTTSendClick('impression','query','查询标签');
        // console.log('gStart '+gStart);
        // 定义请求函数
        function ajaxQuery(userOpenid) {
            var op = userOpenid || "?not_login=1";
            $.ajax({
                method: "get",
                url: url.query + op,
                data: {
                    game : param.game,
                    bid : param.bid,
                    channel: param.channel,
                    works_id : heroId,
                    order_type : param.order_type,
                    start : gStart,
                    num: gNum,
                    sandbox : param.sandbox
                },
                dataType: "jsonp"
              }).done(function( msg ) {
                    // console.log(msg);
                    PTTSendClick('impression','queryOk','查询标签成功');
                    var guidelist = msg.data.guidelist,
                        html = ''
                    for (var i = 0; i < guidelist.length; i++){
                        // 打印印象列表，如果投过票的，标记个class
                        html += '<li class="'+((guidelist[i].vote_info)?'voted':'')+'" data-guide="' + guidelist[i].guide_id + '">' + guidelist[i].guide_content + '</li>';
                    }
                  if (html) {
                    $(selector.show).show();
                    $(selector.list).append(html);
                      curPage += guidelist.length;
                      // console.log('curPage: ' + curPage);
                  } else if (!html && curPage > 0) {
                      PTTSendClick('impression','queryFail','查询标签失败');
                      alert("暂无更多标签！");
                  }
            });
        }
        // 
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                url.sub = fn.getOpenid(userinfo);
                // 登录过，能标记有无投过票
                ajaxQuery(url.sub);
            }, function () {
                // 未登录，无法标记有无投过票
                ajaxQuery();
            });
        });
    }
    // 提交标签
    util.postImpress = function () {
        PTTSendClick('impression','post','提交标签');
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                var $txt = $(selector.input).val().trim();
                if ($txt == "") {
                    alert('标签不能为空');
                    return false;
                } else if ($txt.length > 6) {
                    alert('标签不能超过6个字');
                    return false;
                }
                // console.log($txt)
                // 拼装登录态
                url.sub = fn.getOpenid(userinfo);
                // console.log(url.sub);
                
                // 敏感词监测
                $.ajax({
                    url:url.black,
                    data:{accounttype:0,account:0,platid:0,world:0,callbackdata:0,textcategory:0,gameid:'2645',busi_sign:'0g31L9BCFQRAR68Q6kS3',cmd:2,text:$txt},
                    dataType:"json",
                    success:function(result){
                        // console.log(result);
                        if (result.data.text_check_ret == 1) {
                            alert("输入含有敏感词，请重新输入提交！");
                        } else {
                            PTTSendClick('impression','postCheckOK','提交标签过审');
                            // 提交给接口
                            // console.log("开始提交")
                            // console.log(url.sub);?
                            $.ajax({
                                method: "get",
                                url: url.add + url.sub,
                                data: {
                                    game : param.game,
                                    bid : param.bid,
                                    channel: param.channel,
                                    works_id : param.works_id,
                                    guide_content : $txt,
                                    sandbox : param.sandbox
                                },
                                dataType: "jsonp"
                            }).done(function( msg ) {
                                // console.log(msg);
                                if (msg.status == 'SUCCESS') {
                                    alert('提交成功！');
                                    $(selector.list).prepend('<li class="newAdd">' + $txt + '</li>');
                                    $(selector.show).show();
                                    PTTSendClick('impression','postOK','提交标签成功');
                                } else if (msg.status == 'ERROR' && msg.code == 680907) {
                                    alert('请不要频繁提交标签！');
                                    PTTSendClick('impression','postError680907','频繁提交标签');
                                } else {
                                    alert('请求出错，提交失败！');
                                    PTTSendClick('impression','postError','提交标签失败');
                                }
                            });
                        }
                    }
                });
                PTTSendClick('impression','postLogined','提交标签已登录');
            }, function () {
                alert("登录后才能提交英雄印象标签！");
                TGDialogS('login_select');
                PTTSendClick('impression','upLogined','提交标签没登录');
                return false;
            });
        });
    }
    // 赞 英雄标签
    util.upImpress = function (guideId,obj) {
        if (!guideId) { return }
        PTTSendClick('impression','up','赞标签');
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                // console.log(userinfo)
                // 拼装登录态
                url.sub = fn.getOpenid(userinfo);

                // 提交给接口
                $.ajax({
                    method: "get",
                    url: url.vote + url.sub,
                    data: {
                        game : param.game,
                        bid : param.bid,
                        channel: param.channel,
                        guide_id : guideId,
                        operator_type : 1,
                        sandbox : param.sandbox
                    },
                    dataType: "jsonp"
                }).done(function( msg ) {
                    // console.log(msg);
                    if (msg.status == 'SUCCESS') {
                        alert('支持成功！');
                        obj.addClass("voted");
                        PTTSendClick('impression','upOK','赞标签成功');
                    }
                    PTTSendClick('impression','upFail','赞标签失败');
                });
                PTTSendClick('impression','upLogined','赞标签已登录');
            }, function () {
                alert("登录后才能支持标签！");
                TGDialogS('login_select');
                PTTSendClick('impression','upUnlogin','赞标签没登录');
                return false;
                // qqAndwxLoginout();
             });
        });
    }
    // 加载更多
    util.showMore = function () {
        if ($(selector.show).hasClass("show-less")) {
            $(selector.show).removeClass("show-less");
        } 
        // console.log("开始从第 " +curPage)
        util.queryImpress(param.works_id, curPage, 10);
        PTTSendClick('impression','showMore','点击显示更多');
    }
    // 收起更多
    util.showLess = function () {
        $(selector.show).addClass("show-less");
        PTTSendClick('impression','showLess','收起更多');
    }
    init = function (iID) {
        // 提交按钮事件绑定
        $(selector.submit).on("click", function () {
            util.postImpress();
        });
        // 更多按钮事件绑定
        $(selector.more).on("click", function () {
            util.showMore();
        })
        // 收起按钮事件绑定
        $(selector.hide).on("click", function () {
            util.showLess();
        })
        // 赞标签事件绑定
        $(selector.list).on("click","li",function () {
            if ($(this).hasClass("voted")) {
                alert("该标签您已支持过！")
            } else if ($(this).hasClass("newAdd")) {
                alert("新增标签，请稍后再支持！")
            } else {
                var gId = $(this).attr("data-guide");
                util.upImpress(gId,$(this));
            }
        })
        // 读取前10条标签
        param.works_id = iID;
        util.queryImpress(param.works_id, curPage, 10);
    }
    return {
        init:function(heroid) { init(heroid) },
    }
})();
if (impressionID) {
    heroImpression.init(impressionID);
}
