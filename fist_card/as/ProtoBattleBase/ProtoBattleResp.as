package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleResp
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleResp";
		public var package_root:*;
		public  var message:*;
		public var cardid:int;
		public var point:int;
		public var battle:Vector.<ProtoBattleInfo>;
		public var winUid:int;
		public function ProtoBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			cardid = undefined;
			point = undefined;
			battle = new Vector.<ProtoBattleInfo>();
			winUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.cardid!= undefined)
			{
				serializeObj.cardid = this.cardid;
			}
			serializeObj.point = this.point;
			serializeObj.battle = [];
			for(var i:int = 0;i < this.battle.length;i++)
			{
				serializeObj.battle.push(this.battle[i].serialize());
			}
			if(this.winUid!= undefined)
			{
				serializeObj.winUid = this.winUid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleResp
		{
			cardid = undefined;
			point = undefined;
			battle = new Vector.<ProtoBattleInfo>();
			winUid = undefined;
			if(msgObj.hasOwnProperty("cardid"))
			{
				this.cardid = msgObj.cardid;
			}
			this.point = msgObj.point;
			for(var i:int = 0;i < msgObj.battle.length;i++)
			{
				this.battle.push(new ProtoBattleInfo(package_root).unserialize(msgObj.battle[i]));
			}
			if(msgObj.hasOwnProperty("winUid"))
			{
				this.winUid = msgObj.winUid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}