package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleCPP
	{
		public static const PROTO:String = "ProtoBattle.ProtoBattleCPP";
		public var package_root:*;
		public  var message:*;
		public var first:int;
		public var cards:BattleCardsCPP;
		public var attacker:ProtoBattleTeam;
		public var defender:ProtoBattleTeam;
		public function ProtoBattleCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			first = undefined;
			cards = undefined;
			attacker = undefined;
			defender = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.first = this.first;
			serializeObj.cards = this.cards.serialize();
			serializeObj.attacker = this.attacker.serialize();
			serializeObj.defender = this.defender.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleCPP
		{
			first = undefined;
			cards = undefined;
			attacker = undefined;
			defender = undefined;
			this.first = msgObj.first;
			this.cards = new BattleCardsCPP(package_root).unserialize(msgObj.cards);
			this.attacker = new ProtoBattleTeam(package_root).unserialize(msgObj.attacker);
			this.defender = new ProtoBattleTeam(package_root).unserialize(msgObj.defender);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}