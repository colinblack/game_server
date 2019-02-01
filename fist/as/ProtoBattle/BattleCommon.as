package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BattleCommon
	{
		public static const PROTO:String = "ProtoBattle.BattleCommon";
		public var package_root:*;
		public  var message:*;
		public var stageId:int;
		public var propId:Vector.<int>;
		public function BattleCommon(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			stageId = undefined;
			propId = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.stageId!= undefined)
			{
				serializeObj.stageId = this.stageId;
			}
			serializeObj.propId = [];
			for(var i:int = 0;i < this.propId.length;i++)
			{
				serializeObj.propId.push(this.propId[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BattleCommon
		{
			stageId = undefined;
			propId = new Vector.<int>();
			if(msgObj.hasOwnProperty("stageId"))
			{
				this.stageId = msgObj.stageId;
			}
			for(var i:int = 0;i < msgObj.propId.length;i++)
			{
				this.propId.push(msgObj.propId[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BattleCommon
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}