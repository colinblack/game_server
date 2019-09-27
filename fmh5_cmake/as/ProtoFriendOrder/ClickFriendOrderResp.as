package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class ClickFriendOrderResp
	{
		public static const PROTO:String = "ProtoFriendOrder.ClickFriendOrderResp";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public var newStatus:int;
		public function ClickFriendOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
			newStatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			serializeObj.newStatus = this.newStatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ClickFriendOrderResp
		{
			index = undefined;
			newStatus = undefined;
			this.index = msgObj.index;
			this.newStatus = msgObj.newStatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ClickFriendOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}