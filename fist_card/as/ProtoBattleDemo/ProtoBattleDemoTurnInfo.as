package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoTurnInfo
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoTurnInfo";
		public var package_root:*;
		public  var message:*;
		public var ahp:int;
		public var ap:int;
		public var dhp:int;
		public var dp:int;
		public function ProtoBattleDemoTurnInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ahp = undefined;
			ap = undefined;
			dhp = undefined;
			dp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ahp = this.ahp;
			serializeObj.ap = this.ap;
			serializeObj.dhp = this.dhp;
			serializeObj.dp = this.dp;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoTurnInfo
		{
			ahp = undefined;
			ap = undefined;
			dhp = undefined;
			dp = undefined;
			this.ahp = msgObj.ahp;
			this.ap = msgObj.ap;
			this.dhp = msgObj.dhp;
			this.dp = msgObj.dp;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoTurnInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}