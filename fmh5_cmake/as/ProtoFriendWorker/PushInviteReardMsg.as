package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class PushInviteReardMsg
	{
		public static const PROTO:String = "ProtoFriendWorker.PushInviteReardMsg";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function PushInviteReardMsg(root:*)
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
		public function unserialize(msgObj:*):PushInviteReardMsg
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushInviteReardMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}