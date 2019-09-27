package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class PushVIPLevel
	{
		public static const PROTO:String = "ProtoVIP.PushVIPLevel";
		public var package_root:*;
		public  var message:*;
		public var newLevel:int;
		public function PushVIPLevel(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			newLevel = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.newLevel = this.newLevel;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushVIPLevel
		{
			newLevel = undefined;
			this.newLevel = msgObj.newLevel;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushVIPLevel
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}