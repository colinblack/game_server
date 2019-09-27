package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class ClickFriendOrderReq
	{
		public static const PROTO:String = "ProtoFriendOrder.ClickFriendOrderReq";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public var Status:int;
		public function ClickFriendOrderReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
			Status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			serializeObj.Status = this.Status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ClickFriendOrderReq
		{
			index = undefined;
			Status = undefined;
			this.index = msgObj.index;
			this.Status = msgObj.Status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ClickFriendOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}