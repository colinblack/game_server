package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpgradeHeroByCoinResp
	{
		public static const PROTO:String = "ProtoHero.UpgradeHeroByCoinResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var hero:HeroBaseInfoCPP;
		public function UpgradeHeroByCoinResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
			hero = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.hero = this.hero.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpgradeHeroByCoinResp
		{
			commons = undefined;
			hero = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.hero = new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpgradeHeroByCoinResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}