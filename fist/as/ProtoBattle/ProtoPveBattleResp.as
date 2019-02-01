package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoPveBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoPveBattleResp";
		public var package_root:*;
		public  var message:*;
		public var info:ProtoBattleDemo;
		public var commons:CommonItemsCPP;
		public var hero:Vector.<HeroBaseInfoCPP>;
		public function ProtoPveBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
			commons = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = this.info.serialize();
			serializeObj.commons = this.commons.serialize();
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoPveBattleResp
		{
			info = undefined;
			commons = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
			this.info = new ProtoBattleDemo(package_root).unserialize(msgObj.info);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoPveBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}