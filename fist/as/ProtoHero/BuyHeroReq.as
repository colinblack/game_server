package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BuyHeroReq
	{
		public static const PROTO:String = "ProtoHero.BuyHeroReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public function BuyHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyHeroReq
		{
			heroid = undefined;
			this.heroid = msgObj.heroid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}