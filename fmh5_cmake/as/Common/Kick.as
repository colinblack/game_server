package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class Kick
	{
		public static const PROTO:String = "Common.Kick";
		public var package_root:*;
		public  var message:*;
		public var reason:String;
		public function Kick(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			reason = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.reason = this.reason;
			return serializeObj;
		}
		public function unserialize(msgObj:*):Kick
		{
			reason = undefined;
			this.reason = msgObj.reason;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Kick
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}