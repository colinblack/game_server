package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PushArchiveUp
	{
		public static const PROTO:String = "ProtoPush.PushArchiveUp";
		public var package_root:*;
		public  var message:*;
		public var hero:HeroBaseInfoCPP;
		public function PushArchiveUp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			hero = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.hero = this.hero.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushArchiveUp
		{
			hero = undefined;
			this.hero = new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushArchiveUp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}