package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class ViewAdResp
	{
		public static const PROTO:String = "ProtoOrder.ViewAdResp";
		public var package_root:*;
		public  var message:*;
		public var adBonus:OrderADBonusCPP;
		public function ViewAdResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			adBonus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.adBonus = this.adBonus.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ViewAdResp
		{
			adBonus = undefined;
			this.adBonus = new OrderADBonusCPP(package_root).unserialize(msgObj.adBonus);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ViewAdResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}