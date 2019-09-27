package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class BuildingCPP
	{
		public static const PROTO:String = "ProtoNPCUser.BuildingCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var buildId:int;
		public var position:Vector.<int>;
		public var direct:int;
		public var doneTime:int;
		public var level:int;
		public function BuildingCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			buildId = undefined;
			position = new Vector.<int>();
			direct = undefined;
			doneTime = undefined;
			level = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.buildId = this.buildId;
			serializeObj.position = [];
			for(var i:int = 0;i < this.position.length;i++)
			{
				serializeObj.position.push(this.position[i]);
			}
			serializeObj.direct = this.direct;
			serializeObj.doneTime = this.doneTime;
			serializeObj.level = this.level;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuildingCPP
		{
			ud = undefined;
			buildId = undefined;
			position = new Vector.<int>();
			direct = undefined;
			doneTime = undefined;
			level = undefined;
			this.ud = msgObj.ud;
			this.buildId = msgObj.buildId;
			for(var i:int = 0;i < msgObj.position.length;i++)
			{
				this.position.push(msgObj.position[i]);
			}
			this.direct = msgObj.direct;
			this.doneTime = msgObj.doneTime;
			this.level = msgObj.level;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuildingCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}