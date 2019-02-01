package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemo
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemo";
		public var package_root:*;
		public  var message:*;
		public var attacker:ProtoBattleDemoTeam;
		public var defender:ProtoBattleDemoTeam;
		public var first:int;
		public var attackerWin:Boolean;
		public var turn:Vector.<ProtoBattleDemoTurn>;
		public var info:Vector.<ProtoBattleDemoTurnInfo>;
		public function ProtoBattleDemo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			attacker = undefined;
			defender = undefined;
			first = undefined;
			attackerWin = undefined;
			turn = new Vector.<ProtoBattleDemoTurn>();
			info = new Vector.<ProtoBattleDemoTurnInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.attacker = this.attacker.serialize();
			serializeObj.defender = this.defender.serialize();
			if(this.first!= undefined)
			{
				serializeObj.first = this.first;
			}
			if(this.attackerWin!= undefined)
			{
				serializeObj.attackerWin = this.attackerWin;
			}
			serializeObj.turn = [];
			for(var i:int = 0;i < this.turn.length;i++)
			{
				serializeObj.turn.push(this.turn[i].serialize());
			}
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemo
		{
			attacker = undefined;
			defender = undefined;
			first = undefined;
			attackerWin = undefined;
			turn = new Vector.<ProtoBattleDemoTurn>();
			info = new Vector.<ProtoBattleDemoTurnInfo>();
			this.attacker = new ProtoBattleDemoTeam(package_root).unserialize(msgObj.attacker);
			this.defender = new ProtoBattleDemoTeam(package_root).unserialize(msgObj.defender);
			if(msgObj.hasOwnProperty("first"))
			{
				this.first = msgObj.first;
			}
			if(msgObj.hasOwnProperty("attackerWin"))
			{
				this.attackerWin = msgObj.attackerWin;
			}
			for(var i:int = 0;i < msgObj.turn.length;i++)
			{
				this.turn.push(new ProtoBattleDemoTurn(package_root).unserialize(msgObj.turn[i]));
			}
			for(var i:int = 0;i < msgObj.info.length;i++)
			{
				this.info.push(new ProtoBattleDemoTurnInfo(package_root).unserialize(msgObj.info[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}