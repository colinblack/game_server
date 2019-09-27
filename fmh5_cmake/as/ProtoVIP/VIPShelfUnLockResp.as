package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPShelfUnLockResp
	{
		public static const PROTO:String = "ProtoVIP.VIPShelfUnLockResp";
		public var package_root:*;
		public  var message:*;
		public var shop:ShopCPP;
		public function VIPShelfUnLockResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = this.shop.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPShelfUnLockResp
		{
			shop = undefined;
			this.shop = new ShopCPP(package_root).unserialize(msgObj.shop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPShelfUnLockResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}