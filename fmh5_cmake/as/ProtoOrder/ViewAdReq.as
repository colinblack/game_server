package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class ViewAdReq
	{
		public static const PROTO:String = "ProtoOrder.ViewAdReq";
		public var package_root:*;
		public  var message:*;
		public function ViewAdReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ViewAdReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ViewAdReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}