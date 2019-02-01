package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class SetHeroResp
	{
		public static const PROTO:String = "ProtoHero.SetHeroResp";
		public var package_root:*;
		public  var message:*;
		public function SetHeroResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetHeroResp
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetHeroResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}