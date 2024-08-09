/**
	ajax code
*/
var xml_http_building_link = '请等待，正在建立连接...';
var xml_http_sending = '请等待，正在发送数据...';
var xml_http_loading = '请等待，正在接受数据...';
var xml_http_load_failed = '通信失败，请刷新重新尝试';
var xml_http_data_in_processed = '通信成功，数据正在处理中...';

function Ajax(statusId, recvType) {
	var aj = new Object();
	var clientHeight = scrollTop = 0;
	if(navigator.userAgent.toLowerCase().indexOf('opera') > -1) {
		clientHeight = 0;
		scrollTop = document.body.scrollTop;
	} else {
		clientHeight = 0;
		scrollTop = document.documentElement.scrollTop;
	}
	if(document.getElementById(statusId)) {
		aj.statusId = document.getElementById(statusId);
		document.getElementById(statusId).style.top = (clientHeight +scrollTop)+"px";
	} else {
		var divElement = document.createElement("DIV");
		divElement.className = "ajaxdiv";
		divElement.style.right = 0;
		divElement.style.className = "ajaxdiv";
		divElement.style.top = (clientHeight +scrollTop)+"px";
		divElement.id = statusId;
		document.body.appendChild(divElement);
		aj.statusId = divElement;
	}
	
	aj.targetUrl = '';
	aj.sendString = '';
	aj.recvType = recvType ? recvType : 'HTML';//HTML XML
	aj.resultHandle = null;

	aj.createXMLHttpRequest = function() {
		var request = false;
		if(window.XMLHttpRequest) {
			request = new XMLHttpRequest();
			if(request.overrideMimeType) {
				request.overrideMimeType('text/xml');
			}
		} else if(window.ActiveXObject) {
			var versions = ['Microsoft.XMLHTTP', 'MSXML.XMLHTTP', 'Microsoft.XMLHTTP', 'Msxml2.XMLHTTP.7.0', 'Msxml2.XMLHTTP.6.0', 'Msxml2.XMLHTTP.5.0', 'Msxml2.XMLHTTP.4.0', 'MSXML2.XMLHTTP.3.0', 'MSXML2.XMLHTTP'];
			for(var i=0; i<versions.length; i++) {
				try {
					request = new ActiveXObject(versions[i]);
					if(request) {
						return request;
					}
				} catch(e) {
					//alert(e.message);
				}
			}
		}
		return request;
	}

	aj.XMLHttpRequest = aj.createXMLHttpRequest();

	aj.processHandle = function() {
		aj.statusId.style.display = '';
		if(aj.XMLHttpRequest.readyState == 1) {
			aj.statusId.innerHTML = xml_http_building_link;
		} else if(aj.XMLHttpRequest.readyState == 2) {
			aj.statusId.innerHTML = xml_http_sending;
		} else if(aj.XMLHttpRequest.readyState == 3) {
			aj.statusId.innerHTML = xml_http_loading;
		} else if(aj.XMLHttpRequest.readyState == 4) {
			if(aj.XMLHttpRequest.status == 200) {
				aj.statusId.innerHTML = xml_http_data_in_processed;
				if(aj.recvType == 'HTML') {
					aj.resultHandle(aj.XMLHttpRequest.responseText);
				} else if(aj.recvType == 'XML') {
					aj.resultHandle(aj.XMLHttpRequest.responseXML);
				}
				aj.statusId.style.display = 'none';
			} else {
				aj.statusId.innerHTML = xml_http_load_failed;
			}
		}
	}

	aj.get = function(targetUrl, resultHandle) {
		aj.targetUrl = targetUrl;
		aj.XMLHttpRequest.onreadystatechange = aj.processHandle;
		aj.resultHandle = resultHandle;
		if(window.XMLHttpRequest) {
			aj.XMLHttpRequest.open('GET', aj.targetUrl);
			aj.XMLHttpRequest.send(null);
		} else {
	        aj.XMLHttpRequest.open("GET", targetUrl, true);
	        aj.XMLHttpRequest.send();
		}
	}

	aj.post = function(targetUrl, sendString, resultHandle) {
		aj.targetUrl = targetUrl;
		aj.sendString = sendString;
		aj.XMLHttpRequest.onreadystatechange = aj.processHandle;
		aj.resultHandle = resultHandle;
		aj.XMLHttpRequest.open('POST', targetUrl);
		aj.XMLHttpRequest.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		aj.XMLHttpRequest.send(aj.sendString);
	}
	return aj;
}