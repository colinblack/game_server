package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ActArchiveChipResp
	{
		public static const PROTO:String = "ProtoHero.ActArchiveChipResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var hero:HeroBaseInfoCPP;
		public function ActArchiveChipResp(root:*)
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
			if(this.hero!= undefined)
			{
				serializeObj.hero = this.hero.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ActArchiveChipResp
		{
			commons = undefined;
			hero = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			if(msgObj.hasOwnProperty("hero"))
			{
				this.hero = new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ActArchiveChipResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}