var agt = navigator.userAgent.toLowerCase();
var is_ie = ((agt.indexOf("msie") != -1) && (agt.indexOf("opera") == -1));
if (ajaxcmt) {
	var boxes_cookie = 0;
	var boxesobj  = GE('showboxes');
	var boxesobjs = GE('boxes');
	var digestnum = 0;
	document.onkeydown = function() {
		if (window.event.keyCode==27) {
			if (boxesobj.style.display == '') {
				Close_Boxes();
			}
		}
	}
	Close_Boxes();
}
var cnt = 0;
function quickpost(event,id){
	if ((event.ctrlKey && window.event.keyCode == 13) || (event.altKey && window.event.keyCode == 83)) {
		cnt++;
		if (cnt==1) {
			AddComment(id);
			return cnt=0;
		} else {
			alert('Submission Processing. Please Wait');
		}
	}
}
function Open_Boxes(id){
	if (boxesobj.style.display=='') {
		Close_Boxes();
		return false;
	}
	boxes_cookie = 1;
	mouseover_open(id);
}
function mouseover_open(id){
	if (boxes_cookie == 1) {
		var left = findPosX(GE(id)) + ietruebody().scrollLeft;
		var top  = findPosY(GE(id)) + ietruebody().scrollTop;
		boxesobj.innerHTML = boxesobjs.innerHTML;
		boxesobj.className = boxesobjs.className;
		boxesobj.style.filter = 'alpha(opacity=96);opacity:0.96;';
		boxesobj.style.display = '';
		if (left + boxesobj.offsetWidth > ietruebody().scrollLeft + ietruebody().clientWidth) {
			left -= boxesobj.offsetWidth;
		}
		if (boxesobj.offsetHeight + top > ietruebody().scrollTop + ietruebody().clientHeight) {
			top -= boxesobj.offsetHeight;
		} else {
			top += 15;
		}
		boxesobj.style.top = top + 'px';
		boxesobj.style.left = left + 'px';
	}
	return false;
}
function doc_mousedown(e){
	var e = is_ie ? event : e;
	var _x	= is_ie ? e.x : e.pageX;
	var _y	= is_ie ? e.y + ietruebody().scrollTop : e.pageY;
	var _x1 = boxesobj.offsetLeft;
	var _x2 = boxesobj.offsetLeft + boxesobj.offsetWidth;
	var _y1 = boxesobj.offsetTop - 25;
	var _y2 = boxesobj.offsetTop + boxesobj.offsetHeight;
	if (_x<_x1 || _x>_x2 || _y<_y1 || _y>_y2) {
		Close_Boxes();
	}
}
function findPosX(obj){
	var curleft = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curleft += obj.offsetLeft
			obj = obj.offsetParent;
		}
	} else if (obj.x) {
		curleft += obj.x;
	}
	return curleft - ietruebody().scrollLeft;
}
function findPosY(obj){
	var curtop = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curtop += obj.offsetTop
			obj = obj.offsetParent;
		}
	} else if (obj.y) {
		curtop += obj.y;
	}
	return curtop - ietruebody().scrollTop;
}
function ietruebody(){
	return (document.compatMode && document.compatMode!="BackCompat") ? document.documentElement : document.body;
}
function Addboxes(type,action,id){
	if (!winduid) {
		alert('您还没有登陆或注册，暂时不能使用此功能！');
		return false;
	}
	var url = ajaxurl + '?action=' + action;
	var param = 'id=' + ajax_convert(id) + '&type=' + ajax_convert(type);
	if (action == 'cmditems') {
		var digest = document.getElementsByName('digest');
		for (i=0;i<digest.length;i++) {
			if (digest[i].checked == true) {
				digestnum = digest[i].value;
				param += '&digest=' + ajax_convert(digest[i].value);
				break;
			}
		}
	} else if (action == 'delatc') {
		if(type == 'music'){
			if (!confirm('您确认要删除此音乐专辑？')) {
				return false;
			}
		}else if(type == 'photo'){
			if (!confirm('您确认要删除此相片吗？')) {
				return false;
			}
		}else{
			if (!confirm('您确认要删除此文章？')) {
				return false;
			}
		}
	}
	send_request(url,AddboxesResponse,param);
}
function AddboxesResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'not_login') {
		alert('请注册后再操作');
	} else if (msg[0] == 'illegal_tid') {
		alert('文章ID非法');
	} else if (msg[0] == 'sameuser_right') {
		alert('自己不能删除自己');
	} else if (msg[0] == 'illegal_uid') {
		alert('用户ID非法');
	} else if (msg[0] == 'manager_right') {
		alert('只有创始人才能删除管理员帐号');
	} else if (msg[0] == 'have_print') {
		alert('你已经支持过此文章');
	} else if (msg[0] == 'have_clt') {
		alert('你已经收藏过此项内容');
	} else if (msg[0] == 'group_right') {
		alert('你没有权限进行此操作');
	} else if (msg[0] == 'clt_success') {
		alert('收藏成功');
	} else if (msg[0] == 'foot_success') {
		GE('footnum').innerHTML = parseInt(GE('footnum').innerHTML)+1;
		alert('支持成功');
	} else if (msg[0] == 'success') {
		if (msg[2]) {
			if (msg[1] == 'cmdusers') {
				if (msg[2] > 0) {
					GE(msg[1]).innerHTML = '取消推荐';
				} else {
					GE(msg[1]).innerHTML = '设为推荐';
				}
			}
		} else {
			Close_Boxes();
			var digest = document.getElementsByName('digest');
			for (i=0;i<digest.length;i++) {
				if (digest[i].value == digestnum) {
					digest[i].checked = true;
					break;
				}
			}
		}
		alert('设置成功');
	} else if (msg[0] == 'del_success') {
		alert('删除成功');
		window.location = 'index.php';
	}
	return false;
}
function Close_Boxes(){
	boxescookie_name = 0;
	boxesobj.innerHTML = '';
	boxesobj.className = '';
	boxesobj.style.display = 'none';
	if (is_ie) {
		document.detachEvent('mousedown',doc_mousedown);
	} else {
		document.removeEventListener('mousedown',doc_mousedown,true);
	}
	return false;
}
function AddComment(type,id){
	if (GE('cmtuser').value == '' || GE('cmtcontent').value == '') {
		alert('用户名或评论内容不能为空！');
		return false;
	}
	var url = ajaxurl + '?action=addcomment';
	var param = 'cmtuser=' + ajax_convert(GE('cmtuser').value) + '&cmtcontent=' + ajax_convert(GE('cmtcontent').value) + '&gdcode=' + ajax_convert(GE('gdcode').value) + '&id=' + ajax_convert(id) + '&type=' + ajax_convert(type) + '&qanswer=' + ajax_convert(GE('qanswer').value) + '&qkey=' + ajax_convert(GE('qkey').value);
	send_request(url,AddCommentResponse,param);
}
function AddCommentResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'cmt_empty') {
		alert('用户名或评论内容不能为空！');
	} else if (msg[0] == 'illegal_tid') {
		alert('文章ID非法');
	} else if (msg[0] == 'group_right') {
		alert('你没有权限进行此操作');
	} else if (msg[0] == 'gdcode_error') {
		newgdcode(GE('ck'),GE('ck').src);
		alert('认证码错误');
	} else if (msg[0] == 'word_ban') {
		alert('有不良词语，被禁用');
	} else if (msg[0] == 'time_limit') {
		alert('评论不要快于 ' + msg[1] + ' 秒');
	} else if (msg[0] == 'post_limit') {
		alert('每天你只能发表 ' + msg[1] + ' 篇评论');
	} else if (msg[0] == 'qanswer_error') {
		alert('验证问题答案错误');
		GE('qanswer').value = '';
	} else if (msg[0] == 'success') {
		if (msg[1]) {
			GE('cmtcontent').value = '';
			if (GE('gdcode').value != 0) {
				newgdcode(GE('ck'),GE('ck').src);
				GE('gdcode').value = '';
			}
			var delcmt = ' <a href="javascript:;" onclick="DelComment(\'' + msg[8] + '\',\'' + msg[1] + '\');" class="fr">删除</a>';
			if (msg[7] == 0) {
				delcmt = '';
			}
			GE('newcomment').style.display = '';
			if(ifsumreply == 1){
			GE('rsum').innerHTML = parseInt(GE('rsum').innerHTML)+1;
			}
			if (ajaxtype == 'index') {
				GE('newcomment').innerHTML = '<dl id="' + msg[1] + '">' +delcmt +' <dt><a href="blog.php?uid=' + msg[3] + '"><img src="' + msg[2] + '" class="authorPic" /></a><a href="blog.php?uid=' + msg[3] + '" class="b blue">' + msg[4] + '</a> ' + msg[5] + ' 回复： </dt> <dd>' + msg[6] + '</dd> </dl>' + GE('newcomment').innerHTML;
			} else if (ajaxtype == 'user') {
				GE('cdisplay').style.display = '';
				GE('sums').innerHTML = parseInt(GE('sums').innerHTML)+1;
				GE('newcomment').innerHTML = '<dl id="' + msg[1] + '"> <dd class="comment-pic left"><img src="' + msg[2] + '" width="40" /></dd> <dd>' +delcmt +' <a href="blog.php?uid=' + msg[3] + '" class="big b">' + msg[4] + '</a> <span class="gray">' + msg[5] + '</span> Says: </dd> <dd class="comment-content"><div>' + msg[6] + '</div></dd> </dl>' + GE('newcomment').innerHTML;
			}
			alert('完成操作');
		} else {
			alert('完成操作，等待审核中……');
		}
	}
	return false;
}
function DelComment(type,id){
	var url = ajaxurl + '?action=delcomment';
	var param = 'id=' + ajax_convert(id) + '&type=' + ajax_convert(type);
	send_request(url,DelCommentResponse,param);
}
function DelCommentResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'illegal_cmtid') {
		alert('评论ID非法');
	} else if (msg[0] == 'group_right') {
		alert('你没有权限进行此操作');
	} else if (msg[0] == 'success') {
		GE(msg[1]).style.display = 'none';
		GE('rsum').innerHTML = parseInt(GE('rsum').innerHTML)-1;
		if (ajaxtype == 'user') {
			GE('sums').innerHTML = parseInt(GE('sums').innerHTML)-1;
		}
		alert('完成操作');
	}
	return false;
}

function AddGbook(id){
	if (GE('guser').value == '' || GE('gcontent').value == '') {
		alert('用户名或留言内容不能为空！');
		return false;
	}
	var url	  = ajaxurl + '?action=addgbook';
	var param = 'guser=' + ajax_convert(GE('guser').value) + '&gcontent=' + ajax_convert(GE('gcontent').value) + '&gdcode=' + ajax_convert(GE('gdcode').value) + '&id=' + ajax_convert(id) + '&qanswer=' + ajax_convert(GE('qanswer').value) + '&qkey=' + ajax_convert(GE('qkey').value);
	send_request(url,AddGbookResponse,param);
}
function AddGbookResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'g_empty') {
		alert('用户名或留言内容不能为空！');
	} else if (msg[0] == 'illegal_uid') {
		alert('用户ID非法');
	} else if (msg[0] == 'group_right') {
		alert('你没有权限进行此操作');
	} else if (msg[0] == 'gdcode_error') {
		newgdcode(GE('ck'),GE('ck').src);
		alert('认证码错误');
	} else if (msg[0] == 'word_ban') {
		alert('有不良词语，被禁用');
	} else if (msg[0] == 'time_limit') {
		alert('刷新不要快于 ' + msg[1] + ' 秒');
	} else if (msg[0] == 'post_limit') {
		alert('每天你只能发表 ' + msg[1] + ' 篇评论');
	} else if (msg[0] == 'qanswer_error') {
		alert('验证问题答案错误');
		GE('qanswer').value = '';
	} else if (msg[0] == 'success') {
		if (msg[1]) {
			GE('gcontent').value = '';
			if (GE('gdcode').value != 0) {
				newgdcode(GE('ck'),GE('ck').src);
				GE('gdcode').value = '';
			}
			if (GE('qanswer').value != 0) {
				GE('qanswer').value = '';
			}
			var delg = ' <div class="fr"> <a href="javascript:;" style="cursor:pointer;" onclick="ShowReplyBox(\'' + msg[7] + '\',\'' + msg[1] + '\');">[回复]</a> <a href="javascript:;" style="cursor:pointer;" onclick="DelGbook(\'' + msg[7] + '\',\'' + msg[1] + '\');">[删除]</a> </div>';
			if (msg[8] == 0) {
				delg = '';
			}
			GE('newgbook').style.display = '';
			GE('sum').innerHTML = parseInt(GE('sum').innerHTML)+1;
			GE('newgbook').innerHTML = '<a name="' + msg[1] + '"></a> <dl id="dl_' + msg[1] + '"> <dd class="comment-pic left"><img src="' + msg[2] + '" width="40" /></dd> <dd>' +delg +' <a href="blog.php?uid=' + msg[3] + '" class="big b">' + msg[4] + '</a> <span class="gray">' + msg[5] + '</span> Says: </dd> <dd class="comment-content"> <div>' + msg[6] + '</div> <span id="s_' + msg[1] + '"></span> <div id="r_' + msg[1] + '"> <div class="re-comment" style="display:none;"><div id="r_content_'+ msg[1]+'"></div> </div> </div> </dd> </dl>' + GE('newgbook').innerHTML;
			alert('完成操作');
		}
	}
	return false;
}
function ShowReplyBox(uid,id){
	if (GE('r_' + id).style.display == '') {
		GE('r_' + id).style.display = 'none';
		GE('s_' + id).style.display = '';
		GE('s_' + id).innerHTML = '<div class="re-comment"> <b>回复：</b> <div><textarea class="ip" id="replytext" rows="10" style="width:93%">' + GE('r_content_' + id).innerHTML + '</textarea></div> <input valign="middle" class="bt" type="button" value="回复" onclick="ReplyGbook(\'' + uid + '\',\'' + id + '\')"> </div>';
	} else {
		GE('r_' + id).style.display = '';
		GE('s_' + id).style.display = 'none';
		GE('s_' + id).innerHTML = '';
	}
}
function ReplyGbook(uid,id){
	if (GE('replytext').value == '') {
		alert('回复内容不能为空！');
		return false;
	}
	var url	  = ajaxurl + '?action=replygbook';
	var param = 'replytext=' + ajax_convert(GE('replytext').value) + '&uid=' + ajax_convert(uid) + '&id=' + ajax_convert(id);
	send_request(url,ReplyGbookResponse,param);
}
function ReplyGbookResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'g_empty') {
		alert('回复内容不能为空！');
	} else if (msg[0] == 'illegal_gid') {
		alert('留言ID非法！');
	} else if (msg[0] == 'illegal_uid') {
		alert('用户ID非法！');
	} else if (msg[0] == 'word_ban') {
		alert('有不良词语，被禁用');
	} else if (msg[0] == 'success') {
		GE('s_' + msg[1]).style.display = 'none';
		GE('s_' + msg[1]).innerHTML = '';
		GE('r_' + msg[1]).style.display = '';
		GE('r_' + msg[1]).innerHTML = '<div class="re-comment" style="display:;"> <b>' + msg[2] + ' 于 ' + msg[3] + ' 回复：</b> <div id="r_content_' + msg[1] + '">' + msg[4] + '</div> </div>';
		alert('完成操作');
	}
	return false;
}
function DelGbook(uid,id){
	if (confirm('您确认要删除此条留言！')) {
		var url	  = ajaxurl + '?action=delgbook';
		var param = 'uid=' + ajax_convert(uid) + '&id=' + ajax_convert(id);
		send_request(url,DelGbookResponse,param);
	}
}
function DelGbookResponse(){
	var msg = http_request.responseText;
	msg = msg.split("\t");
	if (msg[0] == 'illegal_gid') {
		alert('留言ID非法！');
	} else if (msg[0] == 'illegal_uid') {
		alert('用户ID非法！');
	} else if (msg[0] == 'success') {
		GE('dl_' + msg[1]).style.display = 'none';
		var sum = parseInt(GE('sum').innerHTML);
		if (sum - 1 < 1) {
			GE('newgbook').style.display = 'none';
		}
		GE('sum').innerHTML = sum-1;
		alert('完成操作');
	}
	return false;
}

function CopyURL(url){
	clipboardData.setData('Text',url);
	alert('复制地址成功，您可以把地址发送給好友一起分享');
}

function CommendToMenu(){
	if (!winduid) {
		alert('您还没有登陆或注册，暂时不能使用此功能！');
		return false;
	}
	var url	  = ajaxurl + '?action=commendtomenu';
	var param = '';
	send_request(url,CommendToMenuResponse,param);
}

function CommendToMenuResponse(){
	var msg = http_request.responseText;
	if(msg == 'nofriend'){
		alert('您暂没有好友！');
	}else{
		GE('commendtomenu').innerHTML = msg + '<input type="button" name="submit" value="推荐" onclick="CommendTo();">';
	}
}

function CommendTo(){
	var fuid = GE('fuid').value;
    var url = ajaxurl + '?action=commendto';
    var param = 'itemid=' + itemid + '&fuid=' + fuid;
    send_request(url,CommendToResponse,param);
}

function CommendToResponse(){
	var msg = http_request.responseText;
	if(msg == 'havecommend'){
		alert('已推荐给该好友，不要重复推荐！');
	}else if(msg == 'success'){
		alert('推荐成功！');
	}else{
		alert('操作失败！');
	}
	GE('commendtomenu').innerHTML = '<a style="cursor:pointer;" title="推荐給好友" onclick="CommendToMenu();">推荐给好友</a>';
}
