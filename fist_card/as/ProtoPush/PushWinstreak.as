package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PushWinstreak
	{
		public static const PROTO:String = "ProtoPush.PushWinstreak";
		public var package_root:*;
		public  var message:*;
		public var count:int;
		public function PushWinstreak(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushWinstreak
		{
			count = undefined;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushWinstreak
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}