package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BuyHeroResp
	{
		public static const PROTO:String = "ProtoHero.BuyHeroResp";
		public var package_root:*;
		public  var message:*;
		public var hero:HeroBaseInfoCPP;
		public var commons:CommonItemsCPP;
		public function BuyHeroResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			hero = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.hero = this.hero.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyHeroResp
		{
			hero = undefined;
			commons = undefined;
			this.hero = new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyHeroResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}