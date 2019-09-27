package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class BuyMaterialInfo
	{
		public static const PROTO:String = "User.BuyMaterialInfo";
		public var package_root:*;
		public  var message:*;
		public var propsid:int;
		public var propscnt:int;
		public function BuyMaterialInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsid = undefined;
			propscnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyMaterialInfo
		{
			propsid = undefined;
			propscnt = undefined;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyMaterialInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}