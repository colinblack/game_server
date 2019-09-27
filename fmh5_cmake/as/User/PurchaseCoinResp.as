package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class PurchaseCoinResp
	{
		public static const PROTO:String = "User.PurchaseCoinResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function PurchaseCoinResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseCoinResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PurchaseCoinResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}