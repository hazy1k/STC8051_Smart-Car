function ShowDir(){
	obj = GE('dirspan');
	if (obj.style.display == '') {
		obj.style.display = 'none';
	} else {
		obj2 = GE('dirbutton');
		obj.style.top	  = findPosY(obj2)+20;
		obj.style.left    = findPosX(obj2);
		obj.style.display = '';
	}
}
function AddDir(){
	var dirname = GE('dirname').value;
	var dirorder = GE('dirorder').value;
	if (dirname) {
		var url = ajaxurl + '?type=' + dirtype + '&action=atcdir&job=add';
		var param = 'dirname=' + ajax_convert(dirname) + '&dirorder=' + ajax_convert(dirorder) + '&uid=' + ajax_convert(uid);
		send_request(url,AddDirResponse,param);
	} else {
		alert('分类名称不能为空！');
		return false;
	}
}
function AddDirResponse(){
	var addid = http_request.responseText;
	if (!addid) {
		alert('非法操作');
		return false;
	}
	
	op = document.createElement('option');
	op.id = 'dirop' + addid;
	op.appendChild(document.createTextNode(GE('dirname').value));
	op.value = addid;
	GE('dirgpslt').appendChild(op);

	obj = GE('dirtbody');
	tb_tr = document.createElement('tr');
	tb_tr.id = 'dir' + addid;
	obj.appendChild(tb_tr);

	tb_td = document.createElement('td');
	tb_td.align = 'center';
	tb_tr.appendChild(tb_td);

	input = document.createElement('input');
	input.id = 'dirnames' + addid;
	input.type = 'text';
	input.size = GE('dirname').size;
	input.value = GE('dirname').value;
	input.className = GE('dirname').className;
	tb_td.appendChild(input);

	tb_td = document.createElement('td');
	tb_td.innerHTML = '<input id="dirorders' + addid + '" size="' + GE('dirorder').size + '" value="' + GE('dirorder').value + '" class="' + GE('dirorder').className + '">' + ' <a href="javascript:;" onclick="EditDir(\'' + addid + '\')" onmouseover="this.style.textDecoration=\'underline\';" onmouseout="this.style.textDecoration=\'none\';">修改</a>' + ' <a href="javascript:;" onclick="DeleteDir(\'' + addid + '\')" onmouseover="this.style.textDecoration=\'underline\';" onmouseout="this.style.textDecoration=\'none\';">删除</a>';

	tb_tr.appendChild(tb_td);

	GE('dirname').value = '';
	GE('dirorder').value = '';
}
function EditDir(dirid){
	dirname = GE('dirnames' + dirid).value;
	dirorder = GE('dirorders' + dirid).value;
	if (!dirname) {
		alert('分类名称不能为空！');
		return false;
	}
	var url = ajaxurl + '?type=' + dirtype + '&action=atcdir&job=edit';
	var param = 'dirname=' + ajax_convert(dirname) + '&dirorder=' + ajax_convert(dirorder) + '&dirid=' + ajax_convert(dirid) + '&uid=' + ajax_convert(uid);
	send_request(url,EditDirResponse,param);
}
function EditDirResponse(){
	var editid = http_request.responseText;
	if (editid) {
		GE('dirop' + editid).text = GE('dirnames' + editid).value;
		alert('分类编辑成功！');
		return true;
	} else {
		alert('分类编辑失败！');
		return false;
	}
}
function DeleteDir(dirid){
	if (confirm('您确认要删除此分类？')) {
		var url = ajaxurl + '?type=' + dirtype + '&action=atcdir&job=delete';
		var param = 'dirid=' + ajax_convert(dirid) + '&uid=' + ajax_convert(uid);
		send_request(url,DeleteDirResponse,param);
	} else {
		return false;
	}
}
function DeleteDirResponse(){
	var deleteid = http_request.responseText;
	if (deleteid) {
		GE('dirtbody').removeChild(GE('dir' + deleteid));
		GE('dirgpslt').removeChild(GE('dirop' + deleteid));
		alert('分类删除成功！');
		return true;
	} else {
		alert('分类删除失败！');
		return false;
	}
}
function AddTag(tagname){
	if (tagname) {
		if (!CheckTag(tagname)) {
			return false;
		}
		var url = ajaxurl + '?type=' + dirtype + '&action=atctag&job=' + control;
		var param = 'tagname=' + ajax_convert(tagname) + '&itemid=' + ajax_convert(itemid) + '&uid=' + ajax_convert(uid);
		send_request(url,AddTagResponse,param);
	} else {
		alert('添加Tag不能为空！');
		return false;
	}
}
function AddTagResponse(){
	var addname = http_request.responseText;
	if (!addname) {
		alert('非法操作');
		return false;
	} else {
		GE('taglist').style.display = '';
		GE('taglist').innerHTML = '<a href="javascript:" title="点击删除此Tag" onclick="DeleteTag(this,\'' + addname + '\')" style="padding-right:3px;">' + addname + '<input name="atc_tagdb[]" type="hidden" value="' + addname + '"></a> ' + GE('taglist').innerHTML;
		GE('tagname').value = '';
	}
}
function DeleteTag(obj,value){
	if (confirm('确定删除Tag')) {
		if (control=='add') {
			DeleteTagResponse(obj);
		} else if (control=='edit') {
			var url = ajaxurl + '?type=' + dirtype + '&action=atctag&job=delete';
			var param = 'tagname=' + ajax_convert(value) + '&itemid=' + ajax_convert(itemid) + '&uid=' + ajax_convert(uid);
			send_request(url,DeleteTagResponse(obj),param);
		}
		alert('Tag删除成功！');
		return true;
	} else {
		return false;
	}
}
function DeleteTagResponse(obj){
	obj.innerHTML = '';
	obj.style.display = 'none';
}
function CheckTag(str){
	str = str.trim();
	var len = str.length;
	if (len<2 || len>10) {
		alert('TAG长度错误');
		return false;
	}
	var chars="`~!@#$%^&*()_-+=|\\{}[]:\";',./<>?";
	for (var i = 0;i < len ;i++) {
		var tmp = chars.indexOf(str.charAt(i));
		if (tmp>=0) {
			alert('TAG含有非法字符 ‘' + str.charAt(i) + '’');
			return false;
		}
	}
	return true;
}
function strlen(str){
	return str.replace(/[^\x00-\xff]/gi,'pw').length;
}

/*
function UploadFile(mode){
	if (GE('atc_attachment' + mode).value != '') {
		var uploadform = GE('FORM');
		var oldaction = uploadform.action;
		var oldonSubmit = uploadform.onSubmit;
		uploadform.action = ajaxurl + '?type=' + dirtype + '&action=upload&job=add&uid='+ ajax_convert(uid) +'&db_uploadmaxsize='+ ajax_convert(uploadmaxsize) +'&db_uploadfiletype='+ ajax_convert(uploadfiletype) +'&db_attachnum='+ ajax_convert(attachnum) +'&mode=' + ajax_convert(mode);
		uploadform.onSubmit = '';
		uploadform.target = 'hideframe';
		uploadform.submit();
		uploadform.action = oldaction;
		uploadform.onSubmit = oldonSubmit;
		uploadform.target = '';
		Showmsg('upload_process');
	} else {
		alert('请选择要上传附件');
	}
}
function UploadFileResponse(mode,aid,size,desc,name,url){
	if (desc == '') {
		desc = '无';
	}
	if (ajaxtype == 'admin') {
		GE('showupload').innerHTML = '<span id="delete' + aid + '"><br /><input name="attachdb[]" type="hidden" value="' + aid + '" /> 描述：<span id="attdesc' + aid + '">' + desc + '</span>&nbsp; 附件：<span id="attname' + aid + '"><a href="' + url + '" target="_blank"><font color="red"><b>' + name + '</b></font></a>&nbsp;(' + size + ' K)&nbsp; <a href="javascript:;" onclick="DeleteFile(\'' + aid + '\')">[删除]</a></span> &nbsp; &nbsp; <a href="javascript:;" onclick="addattach(\'' + aid + '\')"><b>添加到帖子中</b></a></span>';
	} else if (ajaxtype == 'user') {
		GE('showupload').innerHTML = '<div id="delete' + aid + '"> <table border="0" cellpadding="3" cellspacing="0" width="100%" class="div_upload" style="margin-top:5px;"> <tr> <td> 附件：<span id="attname' + aid + '"><a href="' + url + '" target="_blank"><b>' + name + '</b></a> (' + size + ' kB) <input name="attachdb[]" type="hidden" value="' + aid + '" /> &nbsp; <a href="javascript:;" onclick="DeleteFile(\'' + aid + '\')">删除</a> | <a href="javascript:;" onclick="addattach(\'' + aid + '\')">插入到内容</a></span> </td> </tr> <tr> <td> <div style="float:left;">描述：</div> <div id="attdesc' + aid + '" style="float:left;font-weight:bold">' + desc + '</div> </td> </tr> </table> </div>' + GE('showupload').innerHTML;
	}
	GE('showmsg').style.display = 'none';
	GE('atc_desc' + mode).value = '';
	var attachclass = '';
	if (GE('attachtml' + mode).className) {
		attachclass = 'class="' + GE('attachtml' + mode).className + '"';
	}
	GE('attachtml' + mode).innerHTML = '<input type="file" name="atc_attachment' + mode + '" id="atc_attachment' + mode + '" ' + attachclass + ' />';
	alert('文件上传成功！');
}*/
function DeleteFile(aid){
	if (confirm('您确认要删除此附件？')) {
		var uploadform = GE('FORM');
		var oldaction = uploadform.action;
		var oldonSubmit = uploadform.onSubmit;
		uploadform.action = ajaxurl + '?type=' + dirtype + '&action=upload&job=delete&aid=' + ajax_convert(aid) + '&itemid=' + ajax_convert(itemid) + '&uid=' + ajax_convert(uid);
		uploadform.onSubmit = '';
		uploadform.target = 'hideframe';
		uploadform.submit();
		uploadform.action = oldaction;
		uploadform.onSubmit = oldonSubmit;
		uploadform.target = '';
		Showmsg('delete_process');
	} else {
		return false;
	}
}
function DeleteFileResponse(aid){
	GE('delete' + aid).style.display = 'none';
	GE('showmsg').style.display = 'none';
	alert('文件删除成功！');
}
function Showmsg(msg){
	var _msg = {
		'delete_process' : '正在删除中，请稍等......',
		'upload_process' : '正在上传中，请稍等......',
		'upload_content_error' : '附件内容非法,系统已经将其自动删除！',
		'upload_error' : '上传附件失败，造成的原因可能有:附件目录不可写(777)、空间在安全模式下、空间大小已不足。',
		'upload_size_error' : '附件超过指定大小' + uploadmaxsize +'字节。',
		'upload_type_error' : '附件的类型错误，不允许上传此类附件。'
	};
	if (_msg[msg]) {
		msg = _msg[msg];
	}
	GE('showmsg').style.display = '';
	GE('showmsg').innerHTML = msg;
	return true;
}

function addtotext(obj,text){
	if (text) {
		GE(obj).value = text;
	}
}

function showpw(){
	obj = GE('ab_ifhide');
	if(obj.value == 3){
		GE('pwspan').style.display = '';
	}else{
		GE('pwspan').style.display = 'none';
	}
}

function ckpw(){
	var pw = GE('password').value;
	var ckpw = GE('ckpassword').value;
	if(pw != ckpw){
		GE('password').value = '';
		GE('ckpassword').value = '';
		alert('两次输入密码不一致,请重新输入');
	}
}