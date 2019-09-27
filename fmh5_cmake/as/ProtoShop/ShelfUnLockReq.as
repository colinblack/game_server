package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ShelfUnLockReq
	{
		public static const PROTO:String = "ProtoShop.ShelfUnLockReq";
		public var package_root:*;
		public  var message:*;
		public var costdiamond:int;
		public function ShelfUnLockReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			costdiamond = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.costdiamond = this.costdiamond;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShelfUnLockReq
		{
			costdiamond = undefined;
			this.costdiamond = msgObj.costdiamond;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShelfUnLockReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}