package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ViewAdRecycleItemReq
	{
		public static const PROTO:String = "ProtoShop.ViewAdRecycleItemReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public function ViewAdRecycleItemReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ViewAdRecycleItemReq
		{
			ud = undefined;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ViewAdRecycleItemReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}