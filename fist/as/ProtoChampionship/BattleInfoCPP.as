package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BattleInfoCPP
	{
		public static const PROTO:String = "ProtoChampionship.BattleInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var attack:int;
		public var battle:ProtoBattleDemo;
		public var commons:CommonItemsCPP;
		public function BattleInfoCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			attack = undefined;
			battle = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.attack = this.attack;
			if(this.battle!= undefined)
			{
				serializeObj.battle = this.battle.serialize();
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BattleInfoCPP
		{
			attack = undefined;
			battle = undefined;
			commons = undefined;
			this.attack = msgObj.attack;
			if(msgObj.hasOwnProperty("battle"))
			{
				this.battle = new ProtoBattleDemo(package_root).unserialize(msgObj.battle);
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BattleInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}