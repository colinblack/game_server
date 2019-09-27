package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RequestOtherUserBC
	{
		public static const PROTO:String = "User.RequestOtherUserBC";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var myuid:int;
		public function RequestOtherUserBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			myuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.myuid = this.myuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestOtherUserBC
		{
			othuid = undefined;
			myuid = undefined;
			this.othuid = msgObj.othuid;
			this.myuid = msgObj.myuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestOtherUserBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}