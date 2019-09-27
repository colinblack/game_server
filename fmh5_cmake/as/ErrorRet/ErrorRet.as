package com.sanguo.game.server.connectlogic.common.message.ErrorRet
{
	import laya.utils.Byte;
	public class ErrorRet
	{
		public static const PROTO:String = "ErrorRet.ErrorRet";
		public var package_root:*;
		public  var message:*;
		public var errorret:int;
		public var errormsg:String;
		public var requestmsg:String;
		public function ErrorRet(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			errorret = undefined;
			errormsg = undefined;
			requestmsg = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.errorret = this.errorret;
			serializeObj.errormsg = this.errormsg;
			serializeObj.requestmsg = this.requestmsg;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ErrorRet
		{
			errorret = undefined;
			errormsg = undefined;
			requestmsg = undefined;
			this.errorret = msgObj.errorret;
			this.errormsg = msgObj.errormsg;
			this.requestmsg = msgObj.requestmsg;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ErrorRet
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}