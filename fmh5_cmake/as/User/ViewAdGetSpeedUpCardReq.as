package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ViewAdGetSpeedUpCardReq
	{
		public static const PROTO:String = "User.ViewAdGetSpeedUpCardReq";
		public var package_root:*;
		public  var message:*;
		public function ViewAdGetSpeedUpCardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ViewAdGetSpeedUpCardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ViewAdGetSpeedUpCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}