package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleTeam
	{
		public static const PROTO:String = "ProtoBattle.ProtoBattleTeam";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var level:int;
		public var heros:Vector.<ProtoBattleHero>;
		public function ProtoBattleTeam(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			level = undefined;
			heros = new Vector.<ProtoBattleHero>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.uid!= undefined)
			{
				serializeObj.uid = this.uid;
			}
			serializeObj.level = this.level;
			serializeObj.heros = [];
			for(var i:int = 0;i < this.heros.length;i++)
			{
				serializeObj.heros.push(this.heros[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleTeam
		{
			uid = undefined;
			level = undefined;
			heros = new Vector.<ProtoBattleHero>();
			if(msgObj.hasOwnProperty("uid"))
			{
				this.uid = msgObj.uid;
			}
			this.level = msgObj.level;
			for(var i:int = 0;i < msgObj.heros.length;i++)
			{
				this.heros.push(new ProtoBattleHero(package_root).unserialize(msgObj.heros[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleTeam
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}