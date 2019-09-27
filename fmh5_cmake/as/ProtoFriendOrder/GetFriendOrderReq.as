package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class GetFriendOrderReq
	{
		public static const PROTO:String = "ProtoFriendOrder.GetFriendOrderReq";
		public var package_root:*;
		public  var message:*;
		public function GetFriendOrderReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFriendOrderReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFriendOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}